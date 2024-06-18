/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:43:43 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/12 20:54:17 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**ft_error(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static	unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static	void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
	char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			break ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (0);
	nb_strs = ft_get_nb_strs(s, c);
	tab = malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab)
		return (0);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		tab[i] = malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_error(tab));
		ft_strlcpy(tab[i++], next_str, next_str_len + 1);
	}
	tab[i] = 0;
	return (tab);
}

/*
#include "ft_strlcpy.c"

int		main(void)
{
	int i = 0;
	char **tab;

	tab = ft_split("      split       this for   me  !       ", ' ');
	while (i < 5)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}*/