/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/10 19:01:05 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd_infile, int end[2], char *cmd1, char **env)
{
	char	*full_path;
	char	**args;

	dup2(fd_infile, 0);
	dup2(end[1], 1);
	close(end[0]);
	close(fd_infile);
	// might have to free more stuff
	args = ft_split(cmd1, ' ');
	full_path = check_command(args[0], env);
	execve(full_path, args, env);
	free(full_path);
	free_array(args);
}

void	parent_process(int fd_outfile, int end[2], char *cmd2, char **env)
{
	int		status;
	char	*full_path;
	char	**args;

	// Wait for the child process to finish
	waitpid(-1, &status, 0);
	// Redirect the read end of the pipe to standard input
	dup2(end[0], 0);
	// Redirect standard output to the output file
	dup2(fd_outfile, 1);
	close(end[1]);
	close(fd_outfile);
	args = ft_split(cmd2, ' ');
	full_path = check_command(args[0], env);
	execve(full_path, args, env);
	free(full_path);
	free_array(args);
	exit(1);
}

void	pipex(int fd_infile, int fd_outfile, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	// fork left child
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	// if fork() returns 0, we are in the child process
	if (parent == 0)
		child_process(fd_infile, end, cmd[2], env);
	parent_process(fd_outfile, end, cmd[3], env);
}
int	main(int argc, char **argv, char **env)
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
	pipex(fd_infile, fd_outfile, argv, env);
	close(fd_infile);
	close(fd_outfile);
}
