/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/24 12:31:57 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*get_cmd(char **paths, char *cmd)
{											
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	create_childs_bonus(t_pipex p, char **argv, char **envp) //CUIDADO, no es pipex es "p" solo
{
	p.pid = fork();
	if (!p.pid)
	{
		
		if (p.idx == 0) //si estoy en el 1er fork
			sub_dup2(p.infile, p.pipe[1]); //pilla como infile -> infile.txt
		else if (p.idx == p.cmd_nmbs - 1) //si estoy en el último
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile); //pilla como outfile -> outfile.txt
		else //para todos los de en medio
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]); // infile 
				p.cmd_args = ft_split(argv[2 + p.idx], ' ');
		close_pipes_bonus(&p); //si pongo el close arriba, me da fallo
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			//msg_pipe(p.cmd_args[0]); //esto lo pone el tutorial
			perror("Error en el path al comando."); //esto lo pongo yo 
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}

//esto era la parte mandatory
/*void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[0]);
	if (dup2(pipex.infile, 0) == -1)	
		ft_error_msg_2(ERR_DUP2);
	if (dup2(pipex.tube[1], 1) == -1)
		ft_error_msg_2(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	close(pipex.tube[1]);
	if (dup2(pipex.tube[0], 0) == -1)
		ft_error_msg_2(ERR_DUP2);
	if (dup2(pipex.outfile, 1) == -1)
		ft_error_msg_2(ERR_DUP2);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_args(&pipex);
		perror("Error en el path al comando.");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}*/