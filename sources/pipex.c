/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:03:21 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/29 00:21:49 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(char *read_line)
{
	char	**tab;
	int		cmd_count;
	int		pipefd[2];
	pid_t	child_pid;
	int		outfile;
	int		infile;
	char	*line;

	outfile = open("te", O_RDWR);
	infile = open("test", O_RDWR);
	tab = ft_split(read_line, '|');
	cmd_count = 0;
	while (tab[cmd_count])
		cmd_count++;
	pipe(pipefd);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipefd[1]);
		line = get_next_line(pipefd[0]);
		while (line)
		{
			ft_putstr_fd(line, outfile);
			free(line);
			line = get_next_line(pipefd[0]);
		}
		close(pipefd[0]);
		close(outfile);
		close(infile);
		exit(0);
	}
	else
	{
		close(pipefd[0]);


		child_pid = fork();
		if (child_pid == 0)
		{
			line = get_next_line(infile);
			char	*argv[2] = {"", line, NULL};
			
		}
		else
		{
			wait(child_pid);
		}


		close(pipefd[1]);
	}
	close(outfile);
	close(infile);
}
