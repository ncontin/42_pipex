/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/12 19:20:25 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fdin, int end[2], char *cmd, char **env)
{
	char	*full_path;
	char	**args;

	dup2(fdin, 0);
	dup2(end[1], 1);
	close(end[0]);
	close(fdin);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	full_path = check_command(args[0], env);
	if (!full_path)
		handle_errors(cmd, args);
	execve(full_path, args, env);
	perror("execve");
	free(full_path);
	free_array(args);
}

void	parent_process(int fdout, int end[2], char *cmd, char **env)
{
	int		status;
	char	*full_path;
	char	**args;

	waitpid(-1, &status, 0);
	dup2(end[0], 0);
	dup2(fdout, 1);
	close(end[1]);
	close(fdout);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	full_path = check_command(args[0], env);
	if (!full_path)
		handle_errors(cmd, args);
	execve(full_path, args, env);
	free(full_path);
	free_array(args);
	exit(0);
}

void	pipex(int fdin, int fdout, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror(""));
	if (parent == 0)
		child_process(fdin, end, cmd[2], env);
	else
		parent_process(fdout, end, cmd[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int	fdin;
	int	fdout;

	if (argc != 5)
	{
		perror("Invalid arguments");
		exit(1);
	}
	fdin = open(argv[1], O_RDONLY);
	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdin < 0)
		handle_exit(argv[1], 1);
	if (fdout < 0)
		handle_exit(argv[4], 0);
	pipex(fdin, fdout, argv, env);
	close(fdin);
	close(fdout);
	exit(0);
}
