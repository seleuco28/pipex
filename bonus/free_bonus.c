/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 10:38:47 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void free_paths(t_pipex *pipex)
{
    int i;

    i = 0;
    close(pipex->infile);
    close(pipex->outfile);
    while(pipex->cmd_paths[i])
    {
        free(pipex->cmd_paths[i]);
        i++;
    }
    free(pipex->cmd_paths);
}

void    free_args(t_pipex *pipex)
{
    int i;

    i = 0;
    while (pipex->cmd_args[i])
    {
        free(pipex->cmd_args[i]);
        i++;
    }
    free(pipex->cmd_args);
    free(pipex->cmd);
}

void	child_free(t_pipex *pipex)
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

void	pipe_free(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipe);
	ft_error_msg_2(ERR_CMD_PTH);
}