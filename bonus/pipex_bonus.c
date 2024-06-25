/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 10:48:21 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	ft_error_msg_2(char *err)
{
	perror(err);
	exit (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	//if (argc != 5) esto seria solo parte mandatory también
	//	ft_error_msg_2(ERR_INPUT);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_error_msg_2(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR , 0644);
	if (pipex.outfile < 0)
		ft_error_msg_2(ERR_OUTFILE);
	pipex.cmd_nmbs = argc - 3; //cuento los comandos que me entran
	pipex.pipe_nmbs = 2 * (pipex.cmd_nmbs - 1); //4 pipes para 3 argumentos ¿?¿?¿?
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs); // libero este malloc en parent_free_bonus (abajo) 
	if (!pipex.pipe)
		ft_error_msg_2(ERR_MALLOC);
	pipex.cmd_paths = ft_split(find_path(envp), ':'); //lineas 54 y 55 del tutorial, en una sola
	if (!pipex.cmd_paths)
		pipe_free(&pipex);
	create_pipes_bonus(&pipex);
	pipex.idx = -1; //luego cambiarlo a 0 y poner idx++ debajo del while
	while (++(pipex.idx) < pipex.cmd_nmbs)
		create_childs_bonus(pipex, argv, envp); //para crear los hijos de forma dinámica
	close_pipes_bonus(&pipex); //la función close pipes normales no vale
	waitpid(-1, NULL, 0); //Si pid es -1, waitpid espera la finalización de cualquier proceso hijo, independientemente de su grupo de procesos.
	parent_free_bonus(&pipex);
	return (0);
}