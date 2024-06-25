/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:24:43 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/25 12:55:43 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* LIBRERIAS ESTANDAR */

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* LIBRERIAS EXTRAS */ //para las funciones nuevas pipe, execve(), fork() ..etc
// no se pueden poner todas las librerias sys de una, hay que ir una por una
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

/* ERRORES */

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_ARG "Invalid number of arguments"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_FORK "Failed fork"
# define ERR_DUP2 "Failed dup2() -- function"
# define ERR_CMD_PTH "Command path not found"
# define ERR_MALLOC "Failed malloc"

/* Pipex structure */

typedef struct s_pipex
{
    //pid_t   pid1; mandatory
    //pid_t	pid2;   mandatory
	pid_t	pid;
	//int		tube[2]; // comprobar, pero esto en principio no haria falta, solo me servia en mandatory para el unico pipe
    int		infile;
	int		outfile;
	//char	*paths; // churro largo
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		cmd_nmbs; // metido del bonus
	int		pipe_nmbs; // metido del bonus
	int 	*pipe; //un array de dos ints (recordarlo) (el tube[2] del mandatory)
	int		idx; //cambiarle el nombre a esto
}t_pipex;

/* Tube.c */
void	create_childs_bonus(t_pipex p, char **argv, char **envp);
void	close_pipes_bonus(t_pipex *pipex);

/* Free */
void free_paths(t_pipex *pipex); //no se si hace falta o es mandatory
void free_args(t_pipex *pipex);  //no se si hace falta o es mandatory
void	child_free(t_pipex *pipex);
void	pipe_free(t_pipex *pipex);
/* Functions */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_error_msg(char *err);

#endif
