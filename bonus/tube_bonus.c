/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/19 14:51:10 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// ejempmlo de get_cmd() -- "which tr" te da usr/bin/tr 

static char	*get_cmd(char **paths, char *cmd) // va pasando por los churros cortos y mira si el comando está (si esta lo retorna y sino sigue)
{											// como argumentos el 1ro es el churro corto, el segundo es el comando en si el "tr"
	char	*tmp;
	char	*command;

	while (*paths) // para which ls
	{
		tmp = ft_strjoin(*paths, "/"); // al path le meto un /  
		command = ft_strjoin(tmp, cmd); // y hago otro join con el comando y para which ls ya tendriamos "/bin/ls"
		free(tmp);
		//funcion access() : se utiliza para comprobar si un usuario o proceso tiene permisos de acceso a un archivo o directorio específico
		if (access(command, F_OK) == 0) // importante usar la funcion access para checkear que el command existe y es ejecutable, si retorna 0 es que se puede acceder
			return (command); // F_OK antes tenia un 0, comprobar que todo funcione con el F_OK que significa que existe a lo que queremos acceder
		//en access() F_OK para comprobar si el archivo o directorio existe
		// valor de retorno -> 0: Si el usuario o proceso tiene los permisos especificados en mode.
		//					-> -1 si no tiene los permisos o da error
		free(command);
		paths++;
	}
	return (NULL);
}

// RECORDAR STDIN = 0 -- STDOUT = 1 -- STDERR = 2

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]); // cierro el extremo de lectura
	//always close the end of the pipe you don't use, as long as the pipe is open, the other end will 
    //be waiting for some kind of input and will not be able to finish its process
	//////////////////////////////////////////////////////////////////////////////////////////////
	//dup2 lo uso para redireccionar pero en realidad lo que hace es:
	// int dup2(int fd1, int fd2) : it will close fd2 and duplicate the value of fd2 to fd1, or else said, it will redirect fd1 to fd2
	// ************************************************************************* //
	// IMPORTANTE ESTO, Y ES NUEVO add protection if dup2() < 0
	// ************************************************************************* //
	if (dup2(pipex.infile, 0) == -1) //queremos que nuestro infile sea nuestra stdin	
		ft_error_msg_2(ERR_DUP2);
	if (dup2(pipex.tube[1], 1) == -1) // y que end[1](en el tutorial) sea nuestra stdout
		ft_error_msg_2(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[2], ' '); //spliteado cogeme el 2ndo argumento (1er comando) "en el caso de que sea wc -c haciendo el split solo queda el wc"
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]); //cogemos el churro pequeño Y el 1er comando
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando."); //controlar este error mejor también
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	// la ruta que le metemos y que existe en el PC
	// el comando que le metemos nosotros a mano ej: "ls -la"
	// es la variable de entorno (que ponemos en la consola)
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]); // cierro el extremo de escritura
	if (dup2(pipex.tube[0], 0) == -1) //queremos que end[0] de nuestro programa sea el stdin para que lea lo que ha hecho el child
		ft_error_msg_2(ERR_DUP2);
	if (dup2(pipex.outfile, 1) == -1) // y que nuestra salida (sdout) sea por el outfile
		ft_error_msg_2(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[3], ' '); // spliteado cogeme el 3er argumento (el 2ndo comando)
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]); //cogemos el churro pequeño Y el 2ndo comando
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}