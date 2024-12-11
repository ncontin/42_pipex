/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/11 19:22:32 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// might have to free more stuff

void	child_process(int fd_infile, int end[2], char *cmd1, char **env)
{
	char	*full_path;
	char	**args;

	dup2(fd_infile, 0);
	dup2(end[1], 1);
	close(end[0]);
	close(fd_infile);
	args = ft_split(cmd1, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	full_path = check_command(args[0], env);
	if (!full_path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd1, 2);
		ft_putstr_fd("\n", 2);
		free_array(args);
		exit(127);
	}
	execve(full_path, args, env);
	perror("execve");
	free(full_path);
	free_array(args);
}

void	parent_process(int fd_outfile, int end[2], char *cmd2, char **env)
{
	int		status;
	char	*full_path;
	char	**args;

	waitpid(-1, &status, 0);
	dup2(end[0], 0);
	dup2(fd_outfile, 1);
	close(end[1]);
	close(fd_outfile);
	args = ft_split(cmd2, ' ');
	if (!args)
		exit(1);
	full_path = check_command(args[0], env);
	if (!full_path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd2, 2);
		ft_putstr_fd("\n", 2);
		free_array(args);
		exit(127);
	}
	execve(full_path, args, env);
	free(full_path);
	free_array(args);
	exit(0);
}

void	pipex(int fd_infile, int fd_outfile, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror(""));
	if (parent == 0)
		child_process(fd_infile, end, cmd[2], env);
	else
		parent_process(fd_outfile, end, cmd[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
	{
		perror("Invalid arguments");
		exit(1);
	}
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		handle_exit(argv[1], 1);
	if (fd_outfile < 0)
		handle_exit(argv[4], 0);
	pipex(fd_infile, fd_outfile, argv, env);
	close(fd_infile);
	close(fd_outfile);
	exit(0);
}
