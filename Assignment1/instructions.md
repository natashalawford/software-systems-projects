# COMP 206 - Fall 2024 - Assignment 1

Instructor: Jacob Errington

Due: 12 September 2024, 11:59pm.

Learning goal developed & assessed in this assignment:
- Use the command-line interface of Linux to read, write, and manage files.

## Part 1: creating a directory structure

- Create the directory `fall2024-comp206` in your home directory, if it doesn't exist already.
- Create directories `assignments`, `labs`, and `linux-guru` as subdirectories of
  `fall2024-comp206`. The `assignments` subdirectory might already exist for you, in which case you
  do not need to create it.
- If `assignments` exists and contains some numbered directories (0 1 2 3 ...) go ahead and delete
  those numbered directories. They are empty, so you can use `rmdir`.
- Move the entire directory (git repo) containing these instructions into the `assignments`
  subdirectory.
- Rename the directory containing these instructions to `hw1`

Check you did it right: `ls ~/fall2024-comp206/assignments/hw1/.git` should succeed and show a
listing of some strange, internal git files.

Next, get the lecture notes, which I am also distributing via git:

- `cd ~/fall2024-comp206`
- Clone the git repo at the URL `https://gitlab.cs.mcgill.ca/jerrin/fall-2024-comp-206-notes.git`
  into a subdirectory called `notes`. (See #materials on Discord for a small guide.)

## Part 2: transferring files to and from mimi

This will depend on what OS is running on your computer.
I won't give detailed instructions on how to do this; you will need to do some research.

My recommendation is to find a way to install the `rsync` program on your computer. This is a
command-line program for copying files via ssh.

- On Mac, I recommend getting Homebrew set up. Then you can use `brew install rsync`.
- On Windows, I recommend getting the Windows Subsystem for Linux set up. Then in that shell, you
  should be able to do `apt install rsync`.
- On Linux, well if you're running Linux on your computer already, I trust you to figure this out.

To learn how to use rsync, check out this guide:
https://www.digitalocean.com/community/tutorials/how-to-use-rsync-to-sync-local-and-remote-directories#using-rsync-to-sync-with-a-remote-system

You can alternatively install a graphical program, such as Cyberduck or Filezilla. (Just be careful
with the Filezilla installer: I think you need to uncheck a box during installation somewhere to
prevent it from also installing some kind of garbage alongside Filezilla.)

- In the `hw1` directory, create a file called `copying-to-from-mimi.txt`.
- Use vim to edit this file, and in it, answer the following questions:
    - Q1: What program you decided to use on your computer to do the copying to/from Mimi?
    - Q2: What did you do to install this program? (At most two sentences.)
    - Q3: In at most three sentences, describe how to use the program to copy a file from your
      computer onto mimi

Next:

- On Mimi, in your home directory, run `tree -F fall2024-comp206`.
  This will output a textual diagram of the directory structure you created in part 1.
- Take a screenshot of the diagram that was produced.
  Make sure to include in the screenshot the command prompt (the line where you ran `tree -F`),
  clearly showing your username.
- Copy the screenshot from your computer onto mimi, into the `hw1` directory, and rename it to
  `screenshot.png` (or `screenshot.jpg` if it happened to be in jpg format.)

# Submission instructions

After you've written the file `copying-to-from-mimi.txt` in the hw1 directory and copied the
screenshot into the hw1 directory:

- Enter the hw1 directory.
- Run `git add .` to prepare all changes in the repo to be committed.
- Run `git commit -m "completed assignment 1"`

And that's it.

If you do this and then realize you want to change some things, just repeat the git add and git
commit commands.

At midnight on September 13th (so one minute after 11:59pm deadline on September 12th), a script
will copy your hw1 directory, and that will be your submission.

To allow for late submissions according to the policy outlined in the syllabus, the script will
also make copies at midnight on September 14th and on September 15th.

If you intend to submit late, I strongly encourage you to read the policy carefully in the
#syllabus channel on Discord. You need to fill out a form to indicate that you are using one (or
two) of your late-days. The link to the form is in #syllabus.

# Evaluation scheme

This assignment is graded simply on completion.

You get full marks (100%) when you follow all the instructions correctly:
- you created precisely the directory structure described in part 1, with exactly the same names
    - this is assessed by looking at the screenshot you submitted
- the files to submit have exactly the right names
- the submitted screenshot contains the command prompt with your username
- `copying-to-from-mimi.txt` contains answers to the three questions asked in part 2.

You get partial marks (75%) if you did everything, but some details are incorrect,
e.g. files do not have the right names, or the directory structure is missing something, or your
answers to the questions in part 2 don't make sense.

You get a failing grade (50%) if you didn't do everything: e.g. the screenshot or the text file are
missing, or the text file does not answer all three questions.

You get 0% if didn't do the assignment or failed to follow the instructions relating to submission.

For example, if you accidentally name the directory something like HW1 instead of hw1, then the
script will fail to copy your homework directory **and you will get zero,** even if you did
everything else right! **No exceptions will be made for this.**
