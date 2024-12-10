/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/10 14:06:36 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Your program will be executed as follows:
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
•file1 and file2 are file names.
•cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2 */
#include "pipex.h"

char	*find_path(char **env)
{
	int		i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			printf("%d", ft_strlen(env[i]));
			printf("%s", ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
			return (env[i]);
		}
		i++;
	}
	return (0);
}

// void	parse_command(char *cmd, char **env)
// {
// 	// Check in all possible locations if the binary (command) requested by the user exists.
// 	find_path(env);
// }

void	child_process(int fd_infile, int end[2], char *cmd1, char **env)
{
	// char	**args;
	// redirect text of infile in the terminal for cmd1 to read
	dup2(fd_infile, 0);
	// redirect output of cmd1 to the other end of the pipe
	dup2(end[1], 1);
	close(end[0]);
	close(fd_infile);
	char *const args[] = {"ls", NULL};
	char *const envp[] = {NULL};
	execve("/usr/bin/ls", args, envp);
}

void	parent_process(int fd_outfile, int end[2], char *cmd2, char **env)
{
	int	status;

	// Wait for the child process to finish
	waitpid(-1, &status, 0);
	// Redirect the read end of the pipe to standard input
	dup2(end[0], 0);
	// Redirect standard output to the output file
	dup2(fd_outfile, 1);
	close(end[1]);
	close(fd_outfile);
	char *const args[] = {"wc", NULL};
	char *const envp[] = {NULL};
	execve("/usr/bin/wc", args, envp);
	exit(1);
}

void	pipex(int fd_infile, int fd_outfile, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	// fork left child
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	// if fork() returns 0, we are in the child process
	if (parent == 0)
		child_process(fd_infile, end, cmd[2], env);
	parent_process(fd_outfile, end, cmd[3], env);
}
int	main(int argc, char **argv, char **env)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
	{
		ft_putstr_fd("argument error\n", 1);
		printf("%s", find_path(env));
		return (1);
	}
	// open infile for reading
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
	{
		perror("Error opening input file");
		return (1);
	}
	if (fd_outfile < 0)
	{
		perror("Error opening output file");
		return (1);
	}
	pipex(fd_infile, fd_outfile, argv, env);
	close(fd_infile);
	close(fd_outfile);
}
