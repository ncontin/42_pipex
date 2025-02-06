/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:59:09 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/06 17:54:10 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_cmd_not_found(char *cmd, char **args, int is_1st)
{
	if (is_1st == TRUE)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_array(args);
		exit(0);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_array(args);
		exit(127);
	}
}

void	handle_exit(char *str, int is_infile)
{
	if (access(str, F_OK) != 0)
	{
		perror(str);
		// ft_putstr_fd(str, 2);
		// ft_putstr_fd(":no such file or directory: ", 2);
		exit(1);
	}
	else if (access(str, R_OK) != 0)
	{
		if (is_infile == 1)
		{
			perror(str);
			exit(0);
		}
		else
		{
			perror(str);
			exit(1);
		}
	}
	exit(1);
}

void	handle_fork_error(pid_t process)
{
	if (process < 0)
	{
		ft_putstr_fd("Fork error", 2);
		return ;
	}
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
