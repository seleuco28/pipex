/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 16:06:18 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5) //acaba en x no en azul CUIDADO
		ft_error_msg(ERR_ARG);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_error_msg(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR , 0644);
	if (pipex.outfile < 0)
		ft_error_msg(ERR_OUTFILE);
	pipex.cmd_nmbs = argc - 3; //cuento los comandos que me entran
	pipex.pipe_nmbs = 2 * (pipex.cmd_nmbs - 1); //4 salidas pipes para 3 argumentos
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs); // libero este malloc en parent_free_bonus (abajo) 
	if (!pipex.pipe)
		ft_error_msg(ERR_MALLOC);
	pipex.cmd_paths = ft_split(find_path(envp), ':'); //lineas 54 y 55 del tutorial, en una sola
	//if (!pipex.cmd_paths) //tutorial no lo pone, y me parece  bastante engorro
	//	pipe_free(&pipex);
	create_pipes_bonus(&pipex);
	pipex.idx = -1; //luego cambiarlo a 0 y poner idx++ debajo del while
	while (++(pipex.idx) < pipex.cmd_nmbs)
		create_childs_bonus(pipex, argv, envp); //para crear los hijos de forma dinámica
	close_pipes_bonus(&pipex); //la función close pipes normales no vale
	waitpid(-1, NULL, 0); //Si pid es -1, waitpid espera la finalización de cualquier proceso hijo, independientemente de su grupo de procesos.
	parent_free_bonus(&pipex);
	return (0);
}