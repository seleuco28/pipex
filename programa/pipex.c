/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:40 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/22 19:38:15 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	an_error(void)
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
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		an_error();
	pipe(pipex.tube);
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	pipex.pid = fork();
	if (pipex.pid < 0)
		an_error();
	else if (pipex.pid == 0)
		first_child(pipex, argv, envp);
	else
		second_parent(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid, NULL, 0);
	free_paths(&pipex);
	return (0);
}
