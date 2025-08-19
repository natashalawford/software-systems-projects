# Fall 2024 - COMP 206 - Assignment 6

Due date: 31 October 2024, 11:59pm.

This assignment builds on the last one. It involves the following tasks.

1. Creating a more robust test suite for `minicalc`
2. Refactoring the `build` script into a `Makefile`
3. Practice using dynamic memory in preparation for hw7.

The files to submit in this assignment are: `run-tests`, `minicalc.c`, `Makefile`,
`stringbuilder.c`.

## A more robust test suite (5 points)

Move your testing code from hw5 into a new file for this assignment called `run-tests`.
Next, you'll improve your test suite by doing full input-output testing and checking exit codes of
minicalc. Your script will define a function named `it`. Each test case will be a call to that
function. Your script will make many calls to that function to express the test suite.

The `it` function in your script must take the following inputs:

1. A high-level name for this test case.
2. The expected exit code of this test case.
3. The expected stdout of this test case.
4. The expected stderr of this test case.
5. The inputs to minicalc that should produce that output.

For example, we would use the function like this:

```bash
it "correctly finds the gcd of a single number" \
    0 "42" "" \
    "gcd" "42"

it "gives an error message when gcd receives no inputs" \
    2 "" "minicalc: error: gcd requires at least one input" \
    "gcd"
```

Running `./run-tests` should produce output like this:

```bash
$ ./run-tests
correctly finds the gcd of a single number: OK
gives an error message when gcd receives no inputs: FAILED
    expected stdout: ""
    actual stdout: "minicalc: error: gcd requires at least one input"
    expected stderr: "minicalc: error: gcd requires at least one input"
    actual stderr: ""
```

In this example, the bug identified by the test suite is that the error message is being printed to
stdout instead of stderr.

**Evaluation:**

- **5 points:** the script defines the `it` function as specified, and expresses a _complete_ test
  suite for minicalc using it, by checking for every possible failure scenario, and at least one
  success scenario per operation.
- **4 points:** the script defines the `it` function as specified, and expresses an _incomplete_
  test suite for minicalc using it. No more than three tests are missing.
- **3 points:** the script defines the `it` function, but slightly not as specified or expresses a
  _very imcomplete_ test suite for minicalc using it, i.e. more than three tests are missing.
- **2 points:** the script defines a function to represent a single test case, but in a way very
  different from specified; or the test suite contains only a few tests overall.
- **1 point:** the script does not define a function to represent a test case.
- **0 points:** the script doesn't run or is otherwise incoherent.

## Using dynamic memory (5 points)

Write your code for this question a file called `stringbuilder.c`. The purpose of this exercise is
for you to implement an extremely common and useful dynamic data structure often called a _dynamic
array._ You're already familiar with this data structure: Python's `list` is a dynamic array, Java
has it as the `ArrayList` class, C++ calls it `vector` and Rust calls it `vec`. These kinds of
arrays can have elements added to them over time, and consequently "grow".

A dynamic array consists of three things:

1. A pointer to an underlying, fixed-size array that actually holds the data.
2. An integer called the _capacity,_ that is the total size of the fixed-size array.
3. An integer called the _size,_ that is the count of items currently stored inside the underlying
   array.

Suppose a dynamic array will hold items of some type `T`. Then it crucially supports the
following operation:

```c
void push(T const *item);
```

This function makes a copy of the given item, which is being passed by reference via a pointer,
into the underlying array, at index `size`. That's because `size` is the count of items currently
stored in the underlying array, so treating it as an index gives us the "next spot" in the
underlying array. The size is then incremented.

**However,** what if `size == capacity`? In this case, there is no more room inside the underlying
array. The big idea is to allocate a _new underlying array with double the capacity,_ copy all the
items from the current underlying array into the new one, and finally proceed to add the new item
as before.

**In this exercise,** the dynamic array you'll implement is actually of a specific kind, called a
_string builder._ This is a dynamic array holding `char`s, into which we gradually copy in several,
smaller strings, to ultimately build up a large string.

**The prototypes of the functions you're expected to code** are listed in `stringbuilder.h`,
together with explanations of what they do. Besides those, you must define in `stringbuilder.c`
three global variables to hold the underlying pointer, the capacity, and the size of the dynamic
array.

(If you want to get ahead a bit, use a `struct` to hold the stringbuilder's three core pieces, and
modify the function prototypes from `stringbuilder.h` to take pointers to such a struct as input.)

**Besides those functions,** you must define a `main` function that tests the stringbuilder in the
following way:
- Call `sb_init(8)`.
- Append many small strings into the stringbuilder to witness and test out the automatic resizing.
- Call `sb_build()` to obtain the built string, then print it out using printf, to test the
  null-termination.
- Call `sb_destroy()` to release the stringbuilder.
- Do that all over again, and print out both the original built string, and the new one.
- Ensure that all resources are freed before program termination.

A note about null-termination: you don't need to have a null-terminator on the string while it's
inside the builder, since the builder explicitly tracks the size of the underlying array. You only
_need_ to add a NUL byte on the end in `sb_build`, which explicitly returns a null-terminated
string.

Much of this assignment involves copying strings. There is a standard library function `strcpy` for
this **but you should implement your own string copying function.**

**Evaluation:**
- 1 point for the test suite in `main`.
- 1 point for the string copying helper
- 3 points for implementing the interface described in `stringbuilder.h`
    - The most challenging part of that is implementing `sb_append`. There are several possible
      approaches to doing so. Discuss different ideas (in English, not in code!) in Discord.

## Using a Makefile (3 points)

The `build` script from hw5 compiles the `minicalc.c` file into the executable `minicalc`; when
compilation succeeds, the script runs `minicalc` on a variety of inputs to test it. In this
exercise, you will replace the `build` script with a `Makefile`.

- The `Makefile` must define a PHONY target called `test`, such that `make test` runs the
  `run-tests` script from the previous section.
- You must use the dependency-ordering feature of make so that calling `make test` will compile
  `minicalc` if `minicalc` does not exist.
- The `Makefile` must define a target for the `minicalc` executable, and compile it as specified in
  hw5. The `minicalc` executable must have correct dependencies.
- The `Makefile` must define a target for the `stringbuilder` executable, depending on
  `stringbuilder.h` and `stringbuilder.c`.

**Evaluation:**

- **3 points:** the makefile defines the required targets and uses make's dependency-ordering to
  build minicalc when running the test suite, if minicalc does not exist.
- **2 points:** the required targets are defined, but dependencies are incorrect.
- **1 point:** at least one of the required targets are defined.
- **0 points:** the required targets are not defined, or attempting to build them via `make` does
  not work.
