/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:45:09 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/22 11:05:33 by alvelazq         ###   ########.fr       */
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
    pid_t   pid; //refiriendome a process id 1 // ¿?¿??¿?QUE ESTRUCTURA DE DATOS ES PID_T¿?¿?¿?
    int		tube[2]; //esto es el tube con end[1] y end[0]
    int		infile; // sera el stdin del cmd1
	int		outfile; // sera el stdout del cmd2
	char	*paths; // churro largo
	char	**cmd_paths; // churro corto
	char	**cmd_args; // los comandos que le meto
	char	*cmd; // el comando que tiene el PC
}t_pipex;

/* childs.c */
void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_parent(t_pipex pipex, char *argv[], char *envp[]);

/* free.c */
void free_paths(t_pipex *pipex);
void free_args(t_pipex *pipex);

/* FUNCIONES */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif