/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 12:07:32 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	different(t_attr *attr)
{
	freeing_routine(attr);
	attr->i++;
	if (all_attributes(attr->counter))
		return (attr->i);
	else
		error_msg("At least one attribute is not set");//Leakfree
	return (0);
}

void	next_iter(t_attr *attr)
{
	char	*to_free;

	freeing_routine_nofd(attr);
	attr->i++;
	attr->line = get_next_line(attr->fd);
	to_free = leaktrim(attr->line, " \n");
	attr->splitters = ft_split(to_free, ' ');
	free(to_free);
}

int	ending_case(t_attr *attr)
{
	freeing_routine(attr);
	error_msg("Not all attributes set");//Leakfree
	return (0);
}

int	ft_nasp(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strlen(str) - 1 == i)
		return (0);
	return (1);
}

void	valid_map(char *path, t_cub *data)
{
	char	**matrix;
	int		lines;
	t_attr	attr;

	init_attr(&attr, path, data);
	lines = set_attributes(data, attr);
	matrix = get_matrix(path, lines);
	tests(matrix);
	closed_map(matrix, data);
	data->world_map = matrix;
}
