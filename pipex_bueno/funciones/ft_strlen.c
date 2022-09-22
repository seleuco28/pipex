/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:47:37 by alvelazq          #+#    #+#             */
/*   Updated: 2022/09/16 12:29:55 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0); //no se puede poner NULL te salta warning
	while (str[i])
		i++;
	return (i);
}

/*
int main(void)
{
	char *str;
	str = "12345678";
	printf("%zu\n", ft_strlen(str));
	printf("%zu\n" , strlen(str));
	return (0);
}
*/
