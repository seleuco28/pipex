/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:43:56 by alvelazq          #+#    #+#             */
/*   Updated: 2023/02/12 20:55:24 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Save a copy of a string
// The strdup() function allocates sufficient memory for a copy of the string s1, does the copy, and returns a pointer to it.

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", strdup("abc123"));
	printf("%s\n", ft_strdup("abc123"));
	return (0);
}*/
