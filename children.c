/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:32:20 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/10 17:32:43 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_1st_child(int fdin, int end[2], char *cmd, char **env)
{
	char	*full_path;
	char	**args;

	dup2(fdin, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
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
	close(end[0]);
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
