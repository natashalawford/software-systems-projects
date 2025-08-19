#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_CLIENTS 4
FILE *CLIENTS[MAX_CLIENTS] = {0};
// ^ Each connected client is represented as a FILE*
// If that client is not connected, its FILE* will be NULL


void redistribute_message(int sender_index, char *buf) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (i == sender_index || CLIENTS[i] == NULL){
		continue;
	}     	// Try to send the message 
	if (fprintf(CLIENTS[i], "%s", buf) < 0) {
            	perror("Failed to send message to a client. Closing connection.");
            	fclose(CLIENTS[i]);
            	CLIENTS[i] = NULL; // reset
        } else{
		fflush(CLIENTS[i]);
	}
    }
   }

int poll_message(char *buf, size_t len, int client_index) {
	if (CLIENTS[client_index] == NULL) {
        	return 0; // No client at index
    	}	
    if (fgets(buf, len, CLIENTS[client_index]) == NULL) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0; // No data 
        } else {
            perror("Error reading from client");
            fclose(CLIENTS[client_index]);
            CLIENTS[client_index] = NULL; // Reset 
            return 0;
        }
    }
    return 1; // successful
}

void try_add_client(int server_fd){
	int client_fd = accept(server_fd, NULL, NULL);
	    if (client_fd == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // No pending connections
            return;
        } else {
            perror("accept");
            exit(1);
        }
    }
	
    //client_fd to non-blocking mode
    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl client_fd NONBLOCK");
        close(client_fd);
        return;
    }

    // file descriptor to a FILE*
    FILE *client = fdopen(client_fd, "r+");
    if (client == NULL) {
        perror("fdopen");
        close(client_fd);
        return;
    }    

        // Find a slot in the CLIENTS array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (CLIENTS[i] == NULL) {
            CLIENTS[i] = client;
            fprintf(client, "Welcome to the server!\n");
            fflush(client);
            return;
        }
    }

	//If all else fails, slots are full, send a message
	fprintf(client, "Server is currently full! Try again later.\n");
    	fflush(client);
    	fclose(client);
	close(client_fd);
}

int main_loop(int server_fd)
{
    char buf[1024];

    while (1) {
        // check each client to see if there are messages to redistribute
        for (int i = 0; i < MAX_CLIENTS; i++) {
    	if (CLIENTS[i] == NULL) {
        	// Skip unconnected slots
        	continue;
    	}

    	if (!poll_message(buf, sizeof(buf), i)) {
        	// If no message is polled, move to the next client
        	continue;
    }

    printf("Received message from client %i: %s", i, buf);
    redistribute_message(i, buf);
}


        // see if there's a new client to add
        try_add_client(server_fd);

        usleep(100 * 1000); // wait 100ms before checking again
    }
}

int main(int argc, char* argv[])
{
    struct sockaddr_in address;
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1 aka localhost
    // ^ this is a kind of security: the server will only listen
    // for incoming connections that come from 127.0.0.1 i.e. the same
    // computer that the server process is running on.
    address.sin_port = htons(5714);

    if (-1 == bind(server_fd, (struct sockaddr *)&address, sizeof(address))) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (-1 == listen(server_fd, 5)) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    // set the server file descriptor to nonblocking mode
    // so that `accept` returns immediately if there are no pending
    // incoming connections
    if (-1 == fcntl(server_fd, F_SETFL, O_NONBLOCK)) {
        perror("fcntl server_fd NONBLOCK");
        close(server_fd);
        return 1;
    }

    int status = main_loop(server_fd);
    close(server_fd);
    return status;
}
