/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 17:35:47 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	if (dup2(pipex.infile, 0) == -1)
		ft_error_msg(ERR_DUP2);
	if (dup2(pipex.tube[1], 1) == -1)
		ft_error_msg(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		ft_error_msg(ERR_CMD);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	if (dup2(pipex.tube[0], 0) == -1)
		ft_error_msg(ERR_DUP2);
	if (dup2(pipex.outfile, 1) == -1)
		ft_error_msg(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		ft_error_msg(ERR_CMD);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
