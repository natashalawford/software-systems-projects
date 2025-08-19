#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global vars for the string builder:
char *array = NULL;
int capacity = 0;
int size = 0;

//first to initialize w a given capacity:
void sb_init(int init_capacity){
	array = malloc(init_capacity * sizeof(char));
	if (!array) {
		fprintf(stderr, "Memory allocation of list failed. No list created.\n");
	exit(1);
	}
	capacity = init_capacity;
	size = 0; //nothing added yet

	}

void sb_append(const char *buf, int len) {
    //check if new size is larger than capacity, double the size if so:
    if (size + len > capacity) {
        int new_capacity = capacity * 2;
        while (size + len > new_capacity) {
            new_capacity *= 2;
        }

        //create new array with the updated capacity
        char *new_array = malloc(new_capacity * sizeof(char));
        if (!new_array) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }

        //copy existing data from the old array to the new array
        for (int i = 0; i < size; i++) {
            new_array[i] = array[i];
        }

        //free the old array
        free(array);

        //update array and capacity
        array = new_array;
        capacity = new_capacity;
    }

    //copy characters from temp to the end of the array!
    for (int i = 0; i < len && buf[i] != '\0'; i++) {
        array[size++] = buf[i];
    }
}

char * sb_build() {
    char *result = malloc((size + 1) * sizeof(char));
    if (!result) {
        fprintf(stderr, "Memory failed.\n");
        exit(1);
    }
    
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }

    result[size] = '\0';  
    return result;
}

void sb_destroy() {
    free(array);
    array = NULL;
    capacity = 0;
    size = 0;
}


int main() {
    sb_init(8);

    // Test appending small strings
    sb_append("Natasha", 7);    
    sb_append(" is a ", 6);     //double len here should happen
    sb_append(" cool kid", 9);  

    // Build and print the final string
    char *result = sb_build();
    printf("%s\n", result);
    free(result);

    // Clean up and test again
    sb_destroy();
    sb_init(8);
    sb_append("New test +", 10);
    sb_append(" New string", 11);
    result = sb_build();
    printf("%s\n", result);
    free(result);

    sb_destroy();
    return 0;
}


