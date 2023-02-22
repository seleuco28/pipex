/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/22 14:12:42 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	an_error()
{
	perror("Error cerrando el programa");
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		an_error();

	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		an_error();
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR , 0644); //trunc para sobreescr // 0644 para darle permisos y poder borrarlo
	if (pipex.outfile < 0)
		an_error();
	pipe(pipex.tube); // aqui es la unica vez en todo el programa en que hago pipe. Pipe le asigna un FD a cada end[]
	//pipex.paths = find_path(envp); // el churro largo de env: PATH=
	pipex.cmd_paths = ft_split(find_path(envp), ':'); //el churro de arriba spliteado, donde el programa tiene que ir buscando los comandos
	pipex.pid = fork(); // splitea nuestro proceso en dos (cero para child non-cero para paretnt)
	// CONTROLAR CUANDO EL PROCESS ID SEA -1¿¿?¿??¿
	if (pipex.pid < 0)
		an_error();
	else if (pipex.pid == 0) //los id de los child process son siempre CERO
		first_child(pipex, argv, envp); // aqui es donde verdaderamente se ejecuta el codigo.
	else
		second_parent(pipex, argv, envp); // aqui es donde verdaderamente se ejecuta el codigo.
	close_pipes(&pipex);
	waitpid(pipex.pid, NULL, 0);// 1er argumento el pid, 2ndo = NULL : wait until a state change in the child process
									// 3er arguemnto = 0 : wait any child process with the same group ID
	
	free_paths(&pipex);
	//aqui poner el system.out (como en GNL) ¿??¿
	//system("leaks ./pipex");
	return (0);
}