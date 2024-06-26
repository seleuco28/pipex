/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 18:14:59 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		ft_error_msg(ERR_ARG);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_error_msg(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		ft_error_msg(ERR_OUTFILE);
	pipex.cmd_nmbs = argc - 3;
	pipex.pipe_exits = 2 * (pipex.cmd_nmbs - 1);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_exits);
	if (!pipex.pipe)
		ft_error_msg(ERR_MALLOC);
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	create_pipes_bonus(&pipex);
	pipex.counter = -1;
	while (++(pipex.counter) < pipex.cmd_nmbs)
		create_childs_bonus(pipex, argv, envp);
	close_pipes_bonus(&pipex);
	waitpid(-1, NULL, 0);
	parent_free_bonus(&pipex);
	return (0);
}
