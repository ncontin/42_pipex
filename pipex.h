/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/10 17:32:58 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

void	handle_cmd_not_found(char *cmd, char **args, int is_1st);
void	free_array(char **array);
char	*parse_command(char *cmd, char **env);
void	handle_fork_error(pid_t process);
void	process_1st_child(int fdin, int end[2], char *cmd, char **env);
void	process_2nd_child(int fdout, int end[2], char *cmd, char **env);

#endif
