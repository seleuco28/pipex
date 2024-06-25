/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 15:37:39 by alvelazq         ###   ########.fr       */
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

char *find_path(char **envp) // en la consola vas a env
{
	while(ft_strncmp("PATH", *envp, 4)) // hasta que no coincida donde pone PATH vas saltando entre terminos
		envp++;
	return (*envp + 5); // me retornas el churro largo quitandole el "PATH="" (de ahi el +5)
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	ft_error_msg(char *err) //dos tipos de errores, checkear bien el por qué
{
	perror(err);
	exit (0); //para que el programa termine bien (en puntito azul)
}

void	parent_free(t_pipex *pipex)
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
}