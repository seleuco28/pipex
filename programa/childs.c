/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/22 11:03:31 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_cmd(char **paths, char *cmd) // va pasando por los churros cortos y mira si el comando esta (si esta lo retorna y sino sigue)
{
	char	*tmp;
	char	*command;

	while (*paths) // para which ls
	{
		tmp = ft_strjoin(*paths, "/"); // al path le meto un /  
		command = ft_strjoin(tmp, cmd); // y hago otro join con el comando y para which ls ya tendriamos "/bin/ls"
		free(tmp);
		if (access(command, F_OK) == 0) // importante usar la funcion access para checkear que el command existe y es ejecutable, si retorna 0 es que se puede acceder
			return (command); // F_OK antes tenia un 0, comprobar que todo funcione con el F_OK que significa que existe a lo que queremos acceder
		free(command);
		paths++;
	}
	return (NULL);
}

// RECORDAR STDIN = 0 -- STDOUT = 1 -- STDERR = 2

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]); // cierro el extremo de lectura
	dup2(pipex.tube[1], 1); //duplica el fd y le damos el numero de fd que queremos
	dup2(pipex.infile, 0); // colocamos manualmente el infile en el fd 0 (el que es por defecto)
	pipex.cmd_args = ft_split(argv[2], ' '); //spliteado cogeme el 2ndo argumento (1er comando)
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]); //cogemos el comando que tenemos y existe en nuestro PC
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	// la ruta que le metemos y que existe en el PC
	// el comando que le metemos nosotros a mano ej: "ls -la"
	// envp es lo que ponemos en la consola, una enviromental variable
}

void	second_parent(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]); // cierro el extremo de escritura
	dup2(pipex.tube[0], 0); //duplica el fd y le damos el numero de fd que queremos
	dup2(pipex.outfile, 1); // colocamos manualmente el outfile en el fd 1 (el que es por defecto)
	pipex.cmd_args = ft_split(argv[3], ' '); // spliteado cogeme el 3er argumento (el 2ndo comando)
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]); //cogemos el comando que tenemos y existe en nuestro PC
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}