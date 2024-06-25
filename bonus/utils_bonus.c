/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:28 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 17:13:23 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/*void free_paths(t_pipex *pipex) //no se utiliza, es igual que parent_free_bonus
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
}*/

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

/*void	child_free(t_pipex *pipex) //borrar, es igual que free_args
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
}*/

/*void	pipe_free(t_pipex *pipex) //tutorial no lo pone, y me parece un engorro
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipe);
	ft_error_msg(ERR_CMD_PTH);
}*/

char *find_path(char **envp)
{
	while(ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	parent_free_bonus(t_pipex *pipex) //mover esta función a free_bonus.txt
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
	free(pipex->pipe); //agregado en el tutorial liberamos el malloc que en mandatory no hemos hecho
}

void create_pipes_bonus(t_pipex *pipex)
{
	int i = 0;

	while (i < pipex->cmd_nmbs - 1) //CUIDADO, en mi caso estaria creando 2 pipes aqui
	{
		if (pipe(pipex->pipe + 2 * i) < 0) //voy creando pipes y si da  < 0 es error -- 
											//+2 porque es un int * con dos extremos (en el mandatory, le digo explicitamente que tube es un array con dos ints, aqui le pongo ese +2 parra eso) 
			parent_free_bonus(pipex);            // y libero el parent
		i++;
	}
}

/*void	close_pipes(t_pipex *pipex) //de la parte mandatory
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}*/
void	close_pipes_bonus(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nmbs))
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