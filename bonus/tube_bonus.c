/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 18:34:51 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	free_args(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, STDIN_FILENO);
	dup2(first, STDOUT_FILENO);
}

void	create_childs_bonus(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (p.pid == 0)
	{
		if (p.counter == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.counter == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.counter - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.counter - 2], p.pipe[2 * p.counter + 1]);
		close_pipes_bonus(&p);
		p.cmd_args = ft_split(argv[2 + p.counter], ' ');
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			free_args(&p);
			ft_error_msg(ERR_CMD);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}
