/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:23:53 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/12 11:30:49 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**split_env_path(char **env)
{
	int		i;
	char	**paths;

	if (!env)
		return (NULL);
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

static char	*check_cmd_in_path(char *path, char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*parse_command(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	paths = split_env_path(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = check_cmd_in_path(paths[i], cmd);
		if (full_path)
			break ;
		i++;
	}
	free_array(paths);
	return (full_path);
}
