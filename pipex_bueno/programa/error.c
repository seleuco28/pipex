/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:05:14 by alvelazq          #+#    #+#             */
/*   Updated: 2022/09/22 14:49:07 by alvelazq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int msg(char *err)
{
    write(2, err, ft_strlen(err));
    return (1);
}

void msg_error(char *err)
{
    perror(err);
    exit (1);
}