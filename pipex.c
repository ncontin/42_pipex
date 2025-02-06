/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/06 17:24:21 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_1st_child(int fdin, int end[2], char *cmd, char **env)
{
	char	*full_path;
	char	**args;

	dup2(fdin, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fdin);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	full_path = parse_command(args[0], env);
	if (!full_path)
		handle_cmd_not_found(args[0], args, TRUE);
	execve(full_path, args, env);
	perror("execve");
	free(full_path);
	free_array(args);
	exit(EXIT_FAILURE);
}

void	process_2nd_child(int fdout, int end[2], char *cmd, char **env)
{
	char	*full_path;
	char	**args;

	dup2(end[0], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(end[1]);
	close(fdout);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	full_path = parse_command(args[0], env);
	if (!full_path)
		handle_cmd_not_found(args[0], args, FALSE);
	execve(full_path, args, env);
	perror("execve");
	free(full_path);
	free_array(args);
	exit(0);
}

void	pipex(int fdin, int fdout, char **argv, char **env)
{
	int		status;
	int		end[2];
	pid_t	proc_one;
	pid_t	proc_two;

	pipe(end);
	proc_one = fork();
	handle_fork_error(proc_one);
	if (proc_one == 0)
		process_1st_child(fdin, end, argv[2], env);
	proc_two = fork();
	handle_fork_error(proc_two);
	if (proc_two == 0)
		process_2nd_child(fdout, end, argv[3], env);
	close(end[0]);
	close(end[1]);
	waitpid(proc_one, &status, 0);
	waitpid(proc_two, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	int	fdin;
	int	fdout;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid arguments\n", 2);
		return (1);
	}
	fdin = open(argv[1], O_RDONLY);
	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdin < 0)
	{
		handle_exit(argv[1], 1);
		handle_exit(argv[4], 0);
	}
	pipex(fdin, fdout, argv, env);
	close(fdin);
	close(fdout);
}
