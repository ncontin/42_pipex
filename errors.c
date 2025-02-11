/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:59:09 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/11 12:38:29 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_cmd_not_found(char *cmd, char **args)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_array(args);
	exit(127);
}

void	handle_fork_error(pid_t process, int fdin, int fdout, int end[2])
{
	if (process < 0)
	{
		perror("Fork failed");
		close(fdin);
		close(fdout);
		if (end)
		{
			close(end[0]);
			close(end[1]);
		}
		exit(EXIT_FAILURE);
	}
}

void	handle_pipe_error(int fdin, int fdout)
{
	perror("Pipe failed");
	close(fdin);
	close(fdout);
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
