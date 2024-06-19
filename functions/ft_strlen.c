/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:47:37 by alvelazq          #+#    #+#             */
/*   Updated: 2024/06/19 08:52:56 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	str = "123456789";
	printf("%zu\n", ft_strlen(str));
	printf("%zu\n" , strlen(str));
	return (0);
}*/

