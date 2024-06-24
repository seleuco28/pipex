/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/24 09:37:32 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void free_paths(t_pipex *pipex)
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
    //porque al ser puntero de puntero hay que "free a lo que hay en los cajones y los mismos cajones"
}

void    free_args(t_pipex *pipex) // esto lo usamos cuando falla el comando
{
    int i;

    i = 0;
    while (pipex->cmd_args[i]) // tambien liberamos con while lo que hay en los cajones y el cajon en si porque es puntero de puntero
    {
        free(pipex->cmd_args[i]);
        i++;
    }
    free(pipex->cmd_args);
    free(pipex->cmd); // y free al path ultimo
}