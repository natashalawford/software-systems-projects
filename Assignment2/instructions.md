# COMP 206 - Fall 2024 - Assignment 2 - 100 points total

Learning goal developed and assessed in this assignment:
- Write bash scripts to automate development tasks

Before getting started, see the file `starter-code`, which gives a quick tour of the features of
bash scripting that you will need to complete this assignment.

## Q1: Making backups of your homework (50 points)

Recall that `rm` is irreversible on Linux. This is different from Windows or macOS, where
"deleting" a file actually places it into some kind of recycling/trash bin from where you can
restore the file.

This means that making backups is very important on Linux! It sure would be terrible if you
accidentally did `rm -rf ~/fall2024-comp206/assignments`.

**Your task** is to create a script called `backup-hmk`, to be run from the `~/fall2024-comp206`
directory, which creates an archive of your `assignments` directory, under a subdirectory called
"backups".

Example:

```bash
$ cd ~/fall2024-comp206
$ # from here, run the script that is in assignments/hw2/backup-hmk
$ assignments/hw2/backup-hmk
Created backup: backups/assignments-2024-09-11T15:41:00.tar.gz
$ tar tvf backups/assignments-2024-09-11T15:41:00.tar.gz
assignments/
assignments/hw1
assignments/hw1/instructions.md
assignments/hw1/copying-to-from-mimi.txt
assignments/hw1/screenshot.png
...
```

* Your script must create the subdirectory `backups` if it does not exist already.
* Your script must name the archive according to the example.
    * That is, it must include the current date and time (a *timestamp*) from when the script is
      run.
    * The `date` command prints the current date and time, but in the wrong format!
    * See `man date` to see how to control the format of the timestamp.
    * To capture the output of the `date` command into a variable, look up "bash command
      substitution", or see here:
      https://unix.stackexchange.com/questions/440088/what-is-command-substitution-in-a-shell

To learn how to use the `tar` program for creating archives, see this guide written by the folks at
GNU: https://www.gnu.org/software/tar/manual/html_chapter/Tutorial.html

Take notes (in vim) along the way!

**Besides writing the script,** answer these short questions in a file called `using-tar.txt`
(obviously in your `hw2` directory!)

Answer each in at most two lines, giving an example and a brief explanation in words:

- Q1.1: how do you use tar to create an archive?
- Q1.2: how do you use tar to list the contents of an archive?
- Q1.3: how do you use tar to extract the entire contents of an archive?
- Q1.4: by default, where do the files get extracted to?
- Q1.5: what is the significance of the two extensions `.tar.gz`?
- Q1.6: what is a 'tarbomb'? Why could extracting one be dangerous?
    - Read this https://www.linfo.org/tarbomb.html and give a succinct answer.

Of course you could chatgpt all these questions, but then you wouldn't actually be learning
anything from this exercise. That will harm you when you are eventually tested on this material in
a midterm! So do your best to answer by looking things up on google, and in particular using the
GNU tar tutorial I linked above.

### Evaluation of Q1

Skills involved in this problem:
- Creating archives using `tar`
- Redirection
- Checking status codes of commands used in scripts

The different parts of this question are essentially pass-fail:
- 10 points for providing answers (even if it they are not perfectly correct) to all the
  short-answer questions.
- 25 points for your script generating an archive of your assignments directory and placing the
  archive in the correct location.
- 10 points for the archive having the correct name, including the date in the right format.
- 5 points for your script having a shebang line

## Automating getting homework assignments (50 points)

To download this homework assignment, you would have done something like...

```bash
$ cd ~/fall2024-comp206/assignments
$ git clone https://gitlab.cs.mcgill.ca/jerrin/f24comp206-hw2.git hw2
...
git outputs some message about the clone
...
$ cd hw2
$ ls
instructions.md starter-code
```

There are a total of 8 assignments in this course, but the only thing that would realistically
change for downloading any particular assignment would be the number. This is a perfect candidate
for writing a script.

**Your task** is to write a script called `get-assignment` to automate this process.

Running `get-assignment hw1` performs a git clone of the hw1 repo into the hw1 subdirectory of
`assignments`.

In other words, the following session should work:

```bash
$ ls ~/fall2024-comp206/assignments
$ # see, no assignments yet; ls produced no output
$ get-assignment hw1
$ ls ~/fall2024-comp206/assignments
hw1
$ ls ~/fall2024-comp206/assignments/hw1
instructions.md
```

**Evaluation**

Skills involved in this question:
- Using positional parameters
- Basic parsing of command-line arguments, involving conditions
- Redirection
- Checking status codes of commands used in scripts

Your grade for this question will depend on how sophisticated you make your script.

- 50/50 **very sophisticated**
    - your script checks whether the target directory already exists and prompts the user for
      whether they would like to delete the directory with a fresh clone
        - depending on the user's answer, your script either just quits or goes ahead with deleting
          the already existing target directory before running `git clone`.
        - hint: you will need to use the `read` command to accomplish this,
          see here: https://linuxize.com/post/bash-read/
    - your script records the output of `git clone` into a temporary file (see `man mktemp`),
      checks whether the clone succeeds, and only prints the output in case git fails.
    - + all requirements from the lower levels
- 40/50 **sophisticated**
    - your script, when run as `get-assignment -h`, prints out a one-line explanation of how to use
      the script
    - your script, when run without any arguments or with too many arguments, prints an error
      message and invites the user to try `get-assignment -h` for more information.
        - hint: the variable $# contains the count of command-line arguments
        - hint: look up how to use the `test` command to compare integers
    - + all requirements from the lower levels
- 30/50 **basic**
    - your script can be run from any directory
    - your script, when called correctly as `get-assignment hw1` or `get-assignment hw2`, performs
      the clone when the target directory does not already exist.
        - if the target directory already exists, your script produces an error message, although
          this error message might come from the call to `git clone` itself.
    - your script makes use of positional parameter variables
    - + all requirements from lower levels
- 20/50 **insufficient**
    - your script includes a shebang line
    - your script doesn't run properly, perhaps only from certain directories
- 0/50 **not assessable:** the TA is unable to run your script at all

# Submission instructions

In your mimi account, the path `~/fall2024-comp206/assignments/hw2` is a git repo, the latest
commit of which contains the following files:
- `get-assignment` **with the execute permission enabled for all users.**
- `backup-hmk` **with the execute permission enabled for all users.**
- `using-tar.txt`
