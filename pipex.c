/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2025/01/17 18:45:06 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_one(int fdin, int end[2], char *cmd, char **env)
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
	full_path = check_command(args[0], env);
	if (!full_path)
		handle_errors(cmd, args);
	execve(full_path, args, env);
	perror("execve");
	free(full_path);
	free_array(args);
}

void	process_two(int fdout, int end[2], char *cmd, char **env)
{
	char	*full_path;
	char	**args;

	dup2(end[0], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
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
	int		status;
	int		end[2];
	pid_t	proc_one;
	pid_t	proc_two;

	pipe(end);
	proc_one = fork();
	if (proc_one < 0)
		return (perror("Fork: "));
	if (proc_one == 0)
		process_one(fdin, end, cmd[2], env);
	proc_two = fork();
	if (proc_two < 0)
		return (perror("Fork: "));
	if (proc_two == 0)
		process_two(fdout, end, cmd[3], env);
	close(end[0]);
	close(end[1]);
	waitpid(proc_one, &status, 0);
	waitpid(proc_two, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid arguments\n", 2);
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
}
