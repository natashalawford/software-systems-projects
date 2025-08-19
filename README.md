# software-systems-projects
My Projects From McGill Software Systems class taken Fall 2024

### Assignment 1
- Learned to navigate and organize files/directories using the Linux command line.  
- Set up and cloned Git repositories, practiced basic Git commands (`add`, `commit`).  
- Transferred files between local machine and remote server (Mimi) using `rsync`/SSH.  
- Used `vim` for editing files and `tree` for visualizing directory structures.  

### Assignment 2
- Wrote bash scripts to automate tasks like creating backups (`tar`, timestamps, shebangs).  
- Gained experience with command-line argument handling, positional parameters, and conditions.  
- Automated downloading of assignments with `git clone` via a custom script (`get-assignment`).  
- Practiced error handling, redirection, and checking command status codes in bash scripts.

### Assignment 3
- Processed and analyzed CSV data using bash utilities (`cut`, `grep`, pipelines).  
- Structured bash scripts into reusable functions for operations (count, total, average).  
- Implemented input validation, error handling, and handling of missing data.  
- Automated country-wide average population calculations with pipelines and loops.  

### Assignment 4
- Analyzed real web server logs with bash, extracting insights like unique IPs, requests per day, most popular posts, and total data transferred.  
- Gained experience parsing structured text data with utilities, conditions, and pattern matching.  
- Built recursive scripts to traverse directory structures and replicate basic `find` functionality.  
- Extended functionality with a script to compute total file sizes (`wc -c`, summation).

### Assignment 5
- Built a **C mini calculator (minicalc.c)** supporting multiple operations (`sqrt`, `gcd`, `anagram`) with robust input validation and error handling.  
- Practiced parsing strings and handling pointers using `strtod`, `strtol`, and arrays.  
- Implemented structured program design with helper functions and clear separation of concerns.  
- Wrote a **bash build script** to compile with strict flags (`-Wall`, `-lm`) and run automated test cases.  

### Assignment 6
- Refactored testing into a **dedicated test suite (run-tests)** with input/output and exit-code validation via a custom `it` function.  
- Replaced the build script with a **Makefile** using dependency management and a `test` target.  
- Implemented a **dynamic string builder in C (stringbuilder.c)**, practicing dynamic memory allocation, resizing, and manual string operations.  

### Assignment 7
- Built a multi-client chat application in C using sockets (`socket`, `bind`, `listen`, `accept`, `connect`).  
- Implemented server-side message relaying so all connected clients receive each other’s messages.  
- Used non-blocking I/O (`fcntl` with `O_NONBLOCK`) to avoid blocking on `accept` and `fgets`.  
- Applied polling techniques to manage multiple simultaneous I/O sources (stdin, client sockets).  
- Gained experience with concurrency challenges and efficient network programming in C.  

### Assignment 8
- Studied core principles of information security (confidentiality, integrity, availability).  
- Analyzed real-world security scenarios (e.g., ransomware, data breaches) and linked them to infosec pillars.  
- Explored cryptography fundamentals: Diffie-Hellman key exchange, RSA for authentication, and message authentication codes.  
- Completed hands-on hacking challenges:  
  - **Injection attack** on a vulnerable web calculator (arbitrary command execution).  
  - **Reverse engineering / buffer overflow attack** on a C login program using `gdb` and assembly analysis.  
- Practiced writing professional security reports explaining vulnerabilities, exploits, and mitigations.  
