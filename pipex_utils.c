/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:59:09 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/11 19:21:10 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(char *str, int is_infile)
{
	perror(str);
	if (access(str, F_OK) != 0) // file does not exist
		exit(1);
	else if (access(str, R_OK) != 0)
	{
		if (is_infile == 1)
			exit(0);
		else
			exit(1);
	}
	exit(1);
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

// 2 malloc for split so need to free array and arra items
char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

// remember to free full_path
char	*check_command(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*full_path;
	char	*temp;

	i = 0;
	paths = get_paths(env);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	free_array(paths);
	return (0);
}
