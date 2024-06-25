/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:45:09 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 16:28:41 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Libraries */

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

/* Erros defined */

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_ARG "Invalid number of arguments"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found"
# define ERR_FORK "Failed fork"
# define ERR_DUP2 "Failed dup2()"

/* Pipex structure */

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	**cmd_paths; // churro corto
	char	**cmd_args; // los comandos que le meto ej: "wc -c"
	char	*cmd; // el path bien puesto ej: "which ls"
}t_pipex;

/* tube.c */
void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_child(t_pipex pipex, char *argv[], char *envp[]);

/* utils.c */
void	free_paths(t_pipex *pipex);
void	free_args(t_pipex *pipex);
char	*find_path(char **envp);
void	close_pipes(t_pipex *pipex);
void	ft_error_msg(char *err);
void	parent_free(t_pipex *pipex);

/* Functions */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif