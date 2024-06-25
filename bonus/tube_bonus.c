/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:06 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 16:44:44 by alvelazq         ###   ########.fr       */
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
	dup2(zero, STDIN_FILENO); //CAMBIADO COMO LO HACE CODEVAULT
	dup2(first, STDOUT_FILENO); // funciona
	//dup2, 1er argumento: el fd que queremos duplicar
	//		2ndo arg: el valor que le queremos dar  a ese fd (duplicandolo)
}

void	create_childs_bonus(t_pipex p, char **argv, char **envp) //CUIDADO, no es pipex es "p" solo
{
	p.pid = fork(); //forkeo en el parten
	if (!p.pid) //y si retorna 0, estoy en proceso hijo y hago todo
	{
		
		if (p.idx == 0) //si estoy en el 1er fork
			sub_dup2(p.infile, p.pipe[1]); //quiero infile.txt como stdin y el end[1] de stdout
		else if (p.idx == p.cmd_nmbs - 1) //si estoy en el último
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile); //quiero el ultimo pipe como stdin y outfile.txt como stdout
		else //para todos los de en medio
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]); // infile el pipe anterior outfile el pipe siguiente
		close_pipes_bonus(&p); //si pongo el close arriba, me da fallo
		p.cmd_args = ft_split(argv[2 + p.idx], ' ');
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			free_args(&p); //en mandatory esta función es free_args()
			ft_error_msg(ERR_CMD);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}
