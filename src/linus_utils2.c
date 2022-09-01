/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:27:51 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 11:13:55 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	freeing_routine(t_attr *attr)
{
	if (attr->line)
	{
		free(attr->line);
		attr->line = NULL;
	}
	if (attr->splitters)
	{
		free_all(attr->splitters);
		attr->splitters = NULL;
	}
	if (attr->splitters2)
	{
		free_all(attr->splitters2);
		attr->splitters2 = NULL;
	}
	close(attr->fd);
}

void	freeing_routine_nofd(t_attr *attr)
{
	if (attr->line)
	{
		free(attr->line);
		attr->line = NULL;
	}
	if (attr->splitters)
	{
		free_all(attr->splitters);
		attr->splitters = NULL;
	}
	if (attr->splitters2)
	{
		free_all(attr->splitters2);
		attr->splitters2 = NULL;
	}
}

int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	wrong_number(t_attr	*attr)
{
	if (ft_strstrlen(attr->splitters) != 2)
	{
		freeing_routine(attr);
		error_msg("Wrong number of attribute values");//Leakfree
	}
}

int	all_attributes(int counter)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (counter % 10 == 0)
			return (0);
		counter = counter / 10;
		i++;
	}
	return (1);
}
