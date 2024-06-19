/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:01:14 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/19 08:52:47 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"

//copy and concatenate strings with the same input parameters and output result
// the function return the total length of the string they tried to create

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (src[count] != '\0')
		count++;
	i = 0;
	if (dstsize == 0)
		return (count);
	while ((src[i] != '\0') && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

/*
int		main(void)
{
	char	dest[40];
	char	src[] = "Hola buenos diass"; // string de 17
	int		size;
    size = 40;
    
    //printf("%lu\n", strlcpy(dest, src, size)); //si compilo esto no me deja el ./a.out
	printf("%lu\n", ft_strlcpy(dest, src, size));
	printf("%s\n", dest);
}*/
