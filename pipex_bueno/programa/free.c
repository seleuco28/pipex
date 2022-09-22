/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2022/09/22 14:57:17 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void parent_free(t_pipex *pipex)
{
    int i;

    i = 0;
    close(pipex->infile);
    close(pipex->outfile);
    while(pipex->cmd_paths[i]) //haces un while liberando todos los paths
    {
        free(pipex->cmd_paths[i]);
        i++;
    }
    free(pipex->cmd_paths); //y la estructura que lo tenia guardado.
}

void    child_free(t_pipex *pipex)
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