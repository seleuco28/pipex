/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:47:33 by alvelazq          #+#    #+#             */
/*   Updated: 2022/09/16 12:36:55 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	x;
	unsigned int	y;
	char			*str;

	x = -1; //si pongo x = 0? y x+¿?¿?
	y = 0;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[++x]) //si pongo x = 0? y x+¿?¿?
		str[x] = s1[x];
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}

/*
int main(void)
{
	char str1[] = "hola buenas ";
	char str2[] = "como estamos?";
	
	printf("%s\n", ft_strjoin(str1 , str2));
	return (0);
}*/

