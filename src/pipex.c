/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 17:26:49 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error_msg(ERR_ARG);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_error_msg(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		ft_error_msg(ERR_OUTFILE);
	if (pipe(pipex.tube) == -1)
		ft_error_msg(ERR_PIPE);
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_error_msg(ERR_FORK);
	else if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_error_msg(ERR_FORK);
	else if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
