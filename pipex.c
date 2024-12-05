/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:53:58 by ncontin           #+#    #+#             */
/*   Updated: 2024/12/05 12:59:44 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Your program will be executed as follows:
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
•file1 and file2 are file names.
•cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2 */
#include <aio.h>
#include <stdio.h>
#include <unistd.h>

void	pipex(int f1, int f2)
{
	int		end[2];
	pid_t	cpid;

	pipe(end);
	cpid = fork();
	// fork left child
	if (cpid == 0)
	{
		// close pipe end[1] which is unused read
		// close(end[1]);
		// // dup2 redirect the output to the pipe end[1]
		// dup2(end[1], STDOUT_FILENO);
		printf("This is the child");
	}
	else
		printf("This is the parent");
}

void	parse_args(char **argv, char **infile, char **cmd1, char **cmd2, char **outfile)
{
	*infile = argv[1];
	*cmd1 = argv[2];
	*cmd2 = argv[3];
	*outfile = argv[4];
}

int	main(int argc, char **argv)
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}

	parse_args(argv, &infile, &cmd1, &cmd2, &outfile);
	printf("%s %s %s %s\n", infile, cmd1, cmd2, outfile);
}
