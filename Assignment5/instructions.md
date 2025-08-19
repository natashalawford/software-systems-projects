# Fall 2024 - COMP 206 - Assignment 5 - total 20 points

- Due: 24 October 11:59pm
- Submission instructions:
    - A git clone of this repo must be located at `~/fall2024-comp206/assignments/hw5`
    - You must have made a commit to this repo that adds the files `minicalc.c` and `build`
      described below.

This assignment is for you:
- to practice using arrays and handling strings and pointers in C
- to learn about parsing strings
- to explore new parts of the standard library

Learning goals assessed in this assignment:

* Write robust system interactions in C.
* Use appropriate data structures and algorithms in C.
* Organize code in C for readability.
* Write bash scripts for automating development tasks.

The two files you'll write in this assignment are the C program `minicalc.c` and the bash script
`build`.

## Writing a build script

In class, I showed you how useful it is to write a bash script to compile C programs, since the
script will systematically compile the program the same way each time, e.g. with certain useful or
necessary compiler flags.

Write a bash script named `build` to do the following:

- Compile `minicalc.c` into an executable named `minicalc`.
- Use the `-Wall` flag to enable useful compiler warnings about your C program.
- Use the `-lm` flag to include the math library, which will be necessary for one of the operations
  of the mini calculator.
- Only when compilation succeeds: run `minicalc` many times across a variety of inputs to test it.
  Add to this test suite in tandem with the development of minicalc itself.

**Evaluation:**
- Your script does all of the above: get 4 points.
- Otherwise: 0 points.

## Writing the mini calculator

Write your code for this program in a file named `minicalc.c`.

The program's input is its **command-line arguments** -- don't use scanf as that reads from
**stdin**. The command-line arguments will specify an operation to perform followed by some
operands.

Usage: `./minicalc OP ARGS...`

The exact count and nature of the ARGS will vary depending on the operation. The required
operations are the following:

1. Square root: `./minicalc sqrt A`
   - Input: `A` represents a floating-point number.
   - Output: the square root of `A`, formatted to two decimal places.
   - Use the `strtod` function to parse the string that minicalc receives into a `double`. See `man
     strtod` for a description of how to use the function.
   - Use the `sqrt` function of the standard library to compute the square root. See `man sqrt` to
     see what you will need to `#include`.

2. Greatest common divisor: `./minicalc gcd N...`
   - Input: one or more integers.
   - Output: the greatest common divisor of all those integers.
   - This isn't a course on algorithms, so use your favourite search engine to look up the Euclidean
     Algorithm for calculating the GCD of two integers.
   - Use the `strtol` function to parse the strings representing integers into `long`s.
     See `man strtol`.
   - You must effect a **separation of concerns** in your program: the loop that parses the
     strings into integers must be separate from the loop that computes the GCD of all the
     integers.
     **Define the function** `int gcd_many(int len, long arr[])` to compute the GCD of all `long`s
     given as input as an array of size `len`.

3. Anagram: `./minicalc anagram S1 S2`
   - Input: two strings.
   - Output: the string `true` or `false` depending on whether the input strings are anagrams.
   - Two strings are anagrams if the letters of one can be rearranged to form the other. For
     example, `binary` and `brainy` are anagrams.
   - To check whether two strings are anagrams, it suffices to see if they have the same *letter
     frequencies.* Use arrays to store the letter frequencies and then determine whether both
     arrays are equal using a loop.

### Input validation

A big part of this assignment is parsing and validating input.

- Any error messages your program produces must be sent to stderr.
  Use the `fprintf` function to accomplish this.
- Calling `./minicalc` with no arguments should print an error message and exit with code 1.
- Calling `./minicalc OP` with an unknown operation must print an error message and exit with code
  1.
- For each operation, you must check that the correct number of operands are given. If the count of
  given operands is incorrect, print an error message and exit with code 2.
    - `sqrt` requires exactly 1 operands
    - `gcd` requires at least 1 operand.
    - `anagram` requires exactly 2 operands.
- Each operation requires some parsing or validation on its operands. If the parsing or validation
  fails, print an error message and exit with code 3.
    - For `sqrt` the given operand must represent in its entirety a floating-point number.
      You will need to figure out how to use the `endptr` parameter of `strtod` to determine
      whether the *whole* string represents a floating-point number.
      Moreover, for `sqrt` the given number must be nonnegative.
    - For `gcd` the operands must represent integers in their entirety.
      Again, the `endptr` parameter of `strtol` is what you need to use to check this.
      Moreover, for `gcd`, all the input integers must be strictly greater than zero.
    - Don't worry about whether the numbers themselves are too big or too small.
    - For `anagram`, the operands must consist only of lowercase English letters. Check this using
      a loop. Use the `islower` standard library function; see `man islower`.
- `minicalc` should exit with code 0 when it succeeds. (This would normally go without saying.)

### Evaluation

There are 16 points to earn for `minicalc`.

* 8 points are earned for input validation, appropriately printing error messages, and using the
  right exit codes.
    * **8 points:** All failure scenarios are handled, error messages are specific, correct exit codes
      are used for all situations.
    * **6 points:** Most failure scenarios are handled, error messages are not specific, exit codes
      are correct in most cases.
    * **4 points:** Validation is often incorrect, unexpected user input can cause the program to
      crash or perform undefined behaviour, error messages are not specific, exit codes are often
      incorrect.
    * **0 points:** validation is missing or the program doesn't compile.

* 4 points are earned for **code comments.** Quality of comments over quantity of comments.
    * **4 points:** the code contains comments that explain *why* certain design choices were made.
      Each defined function besides `main` is accompanied by a comment that concisely expresses the
      purpose of the function.
    * **3 points:** the code contains comments that explain *how* the program works. Some functions
      are accompanied by comments that express the purpose of the function.
    * **0 or 1 point:** code comments are missing or misleading.

* 4 points are earned for **code organization.**
    * **4 points:** Redundancy in the code is minimized. Concerns are well separated thanks to the
      addition of other helper functions with specific purposes. Control flow nesting is limited to
      a depth of 3.
    * **3 points:** Code has some redundancy. Concerns are mostly separated. Helpers are defined,
      but their purpose is sometimes unclear. Control flow nesting is limited to a depth of 4.
    * **2 points:** Code is very redundant. Concerns are largely intermixed. The only defined
      helper is `gcd_many`.
    * **0 points:** Everything is in `main`.
