/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:23:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 19:33:26 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	free(splitters);
}

void	error_msg(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}
