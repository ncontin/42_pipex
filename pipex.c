/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/09 18:48:22 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Your program will be executed as follows:
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
•file1 and file2 are file names.
•cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2 */
#include <aio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// void	parse_command(char *cmd)
// {
// 	return (0);
// }
void	child_process(int fd_infile, int end[2], char *cmd1)
{
	// char	**args;
	// redirect text of infile in the terminal for cmd1 to read
	dup2(fd_infile, 0);
	// redirect output of cmd1 to the other end of the pipe
	dup2(end[1], 1);
	close(end[0]);
	close(fd_infile);
	// execve(cmd1, argv, envp);// Parse the command
	// args = parse_command(cmd1);
	// // Execute cmd2
	// execve(args[0], args, NULL);
}

void	parent_process(int fd_outfile, int end[2], char *cmd2)
{
	int	status;

	// char	**args;
	// Wait for the child process to finish
	waitpid(-1, &status, 0);
	// Redirect the read end of the pipe to standard input
	dup2(end[0], 0);
	// Redirect standard output to the output file
	dup2(fd_outfile, 1);
	close(end[1]);
	close(fd_outfile);
	// Parse the command
	// args = parse_command(cmd2);
	// // Execute cmd2
	// execve(args[0], args, NULL);
	exit(1);
}

void	pipex(int fd_infile, int fd_outfile, char *cmd1, char *cmd2)
{
	int	end[2];

	pid_t parent; // process id
	// pipe() takes an array of two int, and links them together
	pipe(end);
	// what is done in end[0] is visible to end[1], and vice versa
	// pipe() assigns an fd to each end
	// end[1] will write to the its own fd,
	// and end[0] will read end[1]’s fd and write to its own pipe(end);
	parent = fork();
	// fork left child
	if (parent < 0)
		return (perror("Fork: "));
	// if fork() returns 0, we are in the child process
	if (parent == 0)
		child_process(fd_infile, end, cmd1);
	else
		parent_process(fd_outfile, end, cmd2);
}
int	main(int argc, char **argv)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
	{
		ft_putstr_fd("argument error\n", 1);
		return (1);
	}
	// open infile for reading
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
	{
		perror("Error opening input file");
		return (1);
	}
	if (fd_outfile < 0)
	{
		perror("Error opening output file");
		return (1);
	}
	pipex(fd_infile, fd_outfile, argv[2], argv[3]);
	close(fd_infile);
	close(fd_outfile);
}
