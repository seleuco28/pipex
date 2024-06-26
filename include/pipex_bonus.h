/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:24:43 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/26 16:55:26 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* LIBRERIAS ESTANDAR */

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
# define ERR_DUP2 "Failed dup2() -- function"
# define ERR_MALLOC "Failed malloc"

/* Pipex structure */

typedef struct s_pipex
{
	pid_t	pid;
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
}t_pipex;

/* tube_bonus.c */
void	create_childs_bonus(t_pipex p, char **argv, char **envp);
void	close_pipes_bonus(t_pipex *pipex);

/* utils_bonus.c */
void	free_args(t_pipex *pipex);
void	pipe_free(t_pipex *pipex);
char	*find_path(char **envp);
void	parent_free_bonus(t_pipex *pipex);
void	create_pipes_bonus(t_pipex *pipex);
void	close_pipes_bonus(t_pipex *pipex);
void	ft_error_msg(char *err);

/* Functions */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_error_msg(char *err);

#endif
