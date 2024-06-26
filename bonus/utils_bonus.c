/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 18:35:52 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	parent_free_bonus(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipe);
}

void	create_pipes_bonus(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe (pipex->pipe + 2 * i) < 0)
			parent_free_bonus(pipex);
		i++;
	}
}

void	close_pipes_bonus(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_exits))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	ft_error_msg(char *err)
{
	perror(err);
	exit (0);
}
