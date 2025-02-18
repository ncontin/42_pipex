# Pipex

This project aims to recreate the functionality of the shell pipe operator (`|`) in C. It handles the execution of commands with input/output redirection, similar to how the shell processes commands like: `< file1 cmd1 | cmd2 > file2`

## Table of Contents

- [About](#about)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Error Handling](#error-handling)

## About

Pipex is a program that simulates shell pipes by:

- Reading from input files
- Executing commands
- Managing pipes between processes
- Handling output redirection

## Installation

```bash
git clone https://github.com/ncontin/42_pipex.git
cd pipex
make
```

## Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

Example:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This is equivalent to: `< infile ls -l | wc -l > outfile`

## Functions

The project uses the following main functions:

- `pipe()`
- `fork()`
- `execve()`
- `dup2()`
- `waitpid()`

## Error Handling

- File permissions
- Command not found
- Memory allocation
- Pipe creation failures
- Fork errors

Note: Proper error messages are displayed when any of these issues occur.
