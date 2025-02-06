/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/02/06 16:55:50 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

void	handle_cmd_not_found(char *cmd, char **args, int is_1st);
void	free_array(char **array);
char	*parse_command(char *cmd, char **env);
void	handle_exit(char *str, int is_1st);
void	handle_fork_error(pid_t process);

#endif
