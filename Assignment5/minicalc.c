#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


//GCD HELPER FUNCTION #1: function to find a gcd between two numbers:
//Used by the gcd_many function to find the gcd of each pair of numbers
int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//GCD HELPER FUNCTION #2: gcd for many numbers
//find the first gcd between the 1st two numbers, then use this to gcd
//between the next number in the list and the found gcd of the prev two numbers
int gcd_many(int len, long nums[]){
	int result = nums[0];
	for(int i = 1; i<len; i++) {
		result = gcd(result, nums[i]);
	}
	return result;
}

//ANAGRAM HELPER FUNCTION #1
//Tests to see whether an inputted word is only lowercase english characters!
int is_all_lowercase(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) { //Iterate over each char
        if (!islower(str[i])) {
            return 0; 
        }
    }
    return 1;  //Otherwise, the string contains only lowercase letters
}

//ANAGRAM HELPER FUNCTION #2
//Checks to see if any two words are anagrams, returns true if they are, false if not
int are_anagrams(const char *word1, const char *word2){
	//If words aren't the same length, they cannot be anagrams
	if(strlen(word1) != strlen(word2)){
	return 0;
	}
	
	//Makes array of 26 slots for each char in the alphabet
	int count1[26] = {0};
	int count2[26] = {0};

	//For each char iterated over, add 1 to its corresponding slot
	for (int i = 0; word1[i] != '\0'; i++) {
        	count1[word1[i] - 'a']++;
        	count2[word2[i] - 'a']++;
    	}

	//Check to see if there are any slots that differ in count
	for (int i = 0; i < 26; i++) {
        	if (count1[i] != count2[i]) {
		//return 0 if count is different for any slot
            	return 0;
        	}
    	}
	//If all counts match, the words are anagrams! return true
    	return 1;
}

int main(int argc, char *argv[]) {
    // Check if any operation is provided
    if (argc < 2) {
        fprintf(stderr, "Error: please specify an operation (sqrt, gcd, anagram).\n");
        return 1;
    }

//OPERATION SQUARE ROOT:
    if (strcmp(argv[1], "sqrt") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: sqrt needs exactly 1 operand.\n");
            return 2;
        }

        //Parse and validate the input, then calculate the square root
        char *endptr;
        double num = strtod(argv[2], &endptr);

        //Check if the whole string was converted properly:
        if (*endptr != '\0') {
            fprintf(stderr, "Error: input was not a valid floating-point number\n");
            return 3;
        }

        //Check if the number is negative
        if (num < 0) {
            fprintf(stderr, "Error: Negative input number. Input positive number\n");            return 4;
        }

        //Now display square root if we passed all above checks:
        printf("= %.2f\n", sqrt(num));
	}


//OPERATION GCD:
	else if (strcmp(argv[1], "gcd") == 0) {
	
	//Check for right number of operands
        if (argc < 3) { 
            fprintf(stderr, "Error: gcd needs at least 1 operand.\n");
            return 2;
        }

        long numbers[argc - 2];
        char *endptr;

        //Parse and validate each number argument)
        for (int i = 2; i < argc; i++) {
            numbers[i - 2] = strtol(argv[i], &endptr, 10);

            //Check if the input was a proper number:
            if (*endptr != '\0') {
                fprintf(stderr, "Error: All inputs must be valid integers\n");
                return 3;
            }
            if (numbers[i - 2] <= 0) {
                fprintf(stderr, "Error: gcd operands must be strictly greater than 0\n");
                return 3;
            }
        }

	//if we get all proper arguments, we return the gcd of 'many':
	int result = gcd_many(argc - 2, numbers);
        printf("= %d\n", result);
	}

//OPERATION ANAGRAM
     	else if (strcmp(argv[1], "anagram") == 0) {
        
	//Check for right number of operands
	if (argc != 4) {
            fprintf(stderr, "Error: anagram needs exactly 2 operands\n");
            return 2;
        }

	//Check if all characters in the words are lowercase
	if (!is_all_lowercase(argv[2]) || !is_all_lowercase(argv[3])) {
            fprintf(stderr, "Error: both strings must be only lowercase letters\n");
            return 3;
        }

        //If they are valid words, check if the two strings are anagrams
        if (are_anagrams(argv[2], argv[3])) {
            printf("true\n");
        } else {
            printf("false\n");
        }

    } else {
        // If operation was unknown
        fprintf(stderr, "Error: Unknown operation, use sqrt, gcd, or anagram.\n");
        return 1;
    }

    return 0;
}

