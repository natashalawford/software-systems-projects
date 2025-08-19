#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    struct sockaddr_in address;
    int sock_fd;
    char buf[1024];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1 aka localhost
    address.sin_port = htons(5714);
    // ^ to avoid conflicts with others, change the port number
    // to something else. Reflect that change in server.c

    if (-1 == connect(sock_fd, (struct sockaddr *)&address, sizeof(address))) {
        perror("connect");
        return 1;
    }

    // make stdin nonblocking:
    if (fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl stdin");
        close(sock_fd);
        return 1;
	}


    // make the socket nonblocking:
    if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl socket");
        close(sock_fd);
        return 1;
    }




    FILE *server = fdopen(sock_fd, "r+");
    if (!server) {
        perror("fdopen");
        close(sock_fd);
        return 1;
    }
	

    while (1) {
        // - Complete the below polling loop:
        //      - try to read from stdin, and forward across the socket
	 if (fgets(buf, sizeof(buf), stdin)) {
            if (fprintf(server, "%s", buf) < 0) {
                perror("fprintf to server");
                break;
            }
            fflush(server);
        } else if (errno != EAGAIN && errno != EWOULDBLOCK && feof(stdin) == 0) {
            perror("fgets from stdin");
            break;
        }
        //      - try to read from the socket, and forward to stdout
	if (fgets(buf, sizeof(buf), server)) {
            printf("%s", buf);
            fflush(stdout);
        }  else if (feof(server)) { 
       	printf("Server disconnected.\n");
    	break;
    	}else if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("fgets from server");
            break;
        }



        usleep(100 * 1000); // wait 100ms before checking again
    }

    fclose(server);
    close(sock_fd);

    return 0;
}
