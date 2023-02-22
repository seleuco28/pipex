/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/22 19:38:25 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	dup2(pipex.tube[1], 1);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_parent(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	dup2(pipex.tube[0], 0);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
