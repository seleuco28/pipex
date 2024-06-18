/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/18 13:50:16 by alvelazq         ###   ########.fr       */
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

int	ft_error_msg(char *err) //dos tipos de errores, checkear bien el por qué
{
	write(2, err, ft_strlen(err));
	return (1);
}
void	ft_error_msg_2(char *err) //dos tipos de errores, checkear bien el por qué
{
	perror(err);
	exit (1);
}
//esto hay que ir cambiandolo por el control de errores nuevo
void	an_error()
{
	perror("Error cerrando el programa");
	exit(1);
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

// EL CONTROL DE LEAKS DE OTRAS VECES, NO ME FUNCIONA (checkear otros repos)
/*void	leaks(void)
{
	system("leaks -q ./pipex");
}*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error_msg_2(ERR_INPUT); //si le pongo la primera función, me da fallo el tester (checkear esto)
									//# 06: The program does not crash with two parameters [KO]
	//atexit(leaks);

	pipex.infile = open(argv[1], O_RDONLY); //Flag de apertura con permisos solo de lectura
	if (pipex.infile < 0)
		ft_error_msg_2(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR , 0644); //trunc para sobreescr // 0644 para darle permisos y poder borrarlo
	//cuidado aquí, en este caso, siempre será argv[4] pero lo pongo de esta manera, para que cuando gestione multiples pipes me abra siempre el último
	//FLAGS DE APERTURA:
	//O_TRUNC: si el archivo ya existe, pone a cero todos los bytes (lo sobreescribe)
	// O_CREAT: si el archivo no existe lo crea
	// O_RDWR: para que el archivo se abra en lectura y escritura
	// 0644 : permisos de chmod (propietario: lectura, escritura y ejecución
	//							grupo: lectura y escritura
	//							otros usuarios: lectura)
	if (pipex.outfile < 0)
		ft_error_msg_2(ERR_OUTFILE);
	if (pipe(pipex.tube) == -1) 	//esto lo he cambiado, si devuelve 0 todo okey si devuelve -1 error
		ft_error_msg_2(ERR_PIPE);	//pipex.tube -- es el array de dos ints que queremos comunicar
									// pipe() takes an array of two int such as int end[2], and links them together. 
									//In a pipe, what is done in end[0] is visible to end[1], and vice versa. Plus, pipe() assigns an fd to each end.
	//pipex.paths = find_path(envp); // el churro largo de env: PATH=
	pipex.cmd_paths = ft_split(find_path(envp), ':'); //el churro de arriba spliteado, donde el programa tiene que ir buscando los comandos
	pipex.pid1 = fork(); // splitea nuestro proceso en dos (cero para child non-cero para paretnt)
						// crea un nuevo proceso, el child, identico al parent menos por que tiene diferene pid
						//fork to run two processes in one single program
	if (pipex.pid1 == -1) // en el tutorial_clásico dice que hay que controlarlo y el video de codevault tambien
		ft_error_msg_2(ERR_FORK);    //antes tenia puesto si pid <0 (pero si fork() falla solo devuelve -1)
	else if (pipex.pid1 == 0) //los id de los child process son siempre CERO
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_error_msg_2(ERR_FORK);
	else if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);// 1er argumento el pid, 2ndo = NULL : wait until a state change in the child process
									// 3er arguemnto = 0 : wait any child process with the same group ID
	waitpid(pipex.pid2, NULL, 0);
	//free_paths(&pipex); //esta era mi manera
	parent_free(&pipex); //checkear si la de arriba me vale o no, o hacerlo a mi manera
	//aqui poner el system.out (como en GNL) ¿??¿
	//system("leaks ./pipex");
	return (0);
}