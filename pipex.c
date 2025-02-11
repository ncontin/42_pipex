/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/11 12:54:04 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fds_and_pipe(int end[2], int fdin, int fdout)
{
	close(end[0]);
	close(end[1]);
	close(fdin);
	close(fdout);
}

static void	wait_children_and_exit(pid_t proc_one, pid_t proc_two, int status)
{
	waitpid(proc_one, &status, 0);
	waitpid(proc_two, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	pipex(int fdin, int fdout, char **argv, char **env)
{
	int		status;
	int		end[2];
	pid_t	proc_one;
	pid_t	proc_two;

	status = 0;
	if (pipe(end) < 0)
		handle_pipe_error(fdin, fdout);
	proc_one = fork();
	handle_fork_error(proc_one, fdin, fdout, end);
	if (proc_one == 0)
	{
		close(fdout);
		process_1st_child(fdin, end, argv[2], env);
	}
	proc_two = fork();
	handle_fork_error(proc_two, fdin, fdout, end);
	if (proc_two == 0)
	{
		close(fdin);
		process_2nd_child(fdout, end, argv[3], env);
	}
	close_fds_and_pipe(end, fdin, fdout);
	wait_children_and_exit(proc_one, proc_two, status);
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
		perror(argv[1]);
		fdin = open("/dev/null", O_RDONLY);
	}
	if (fdout < 0)
	{
		perror(argv[4]);
		exit(1);
	}
	pipex(fdin, fdout, argv, env);
}
