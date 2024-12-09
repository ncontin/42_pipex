# 42_pipex
The purpose of this project is to try and replicate the workings of the shell pipe operator in a C program


# Main Function

Check if the number of arguments is 5 (program name + 4 arguments).
Open infile for reading.
Open outfile for writing (create if it doesn't exist, truncate if it does).
If any file fails to open, print an error and exit.
Call the pipex function with the file descriptors and commands.
Close the file descriptors.
Return 0.

# Pipex Function

Create a pipe.
Fork the process.
If fork fails, print an error and exit.
If in the child process:
Call child_process with infile descriptor, pipe ends, and cmd1.
If in the parent process:
Call parent_process with outfile descriptor, pipe ends, and cmd2.

# Child Process Function

Redirect infile to standard input.
Redirect the write end of the pipe to standard output.
Close both ends of the pipe.
Execute cmd1 using execlp.
If execution fails, print an error and exit.

# Parent Process Function

Redirect the read end of the pipe to standard input.
Redirect outfile to standard output.
Close both ends of the pipe.
Execute cmd2 using execlp.
If execution fails, print an error and exit.
This pseudocode outlines the basic structure and flow of the pipex project. You can use this as a guide to implement the actual code.

