/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:45:09 by alvelazq          #+#    #+#             */
/*   Updated: 2022/09/22 17:39:16 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# define ERR_INPUT "Invalid number of arguments. \n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

/* ESTRUCTURA PIPEX */

typedef struct s_pipex
{
    pid_t   pid1; //refiriendome a process id 1
    pid_t   pid2; // a process id 2
    int		tube[2]; //esto es el tube con end[1] y end[0]
    int		infile; // sera el stdin del cmd1
	int		outfile; // sera el stdout del cmd2
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

/* childs.c */
void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_child(t_pipex pipex, char *argv[], char *envp[]);

/* free.c */
void parent_free(t_pipex *pipex);
void child_free(t_pipex *pipex);

/* error.c */
void msg_error(char *err);
int	msg(char *err);

/* FUNCIONES */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif