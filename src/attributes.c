/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 16:36:56 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	different(t_attr *attr)
{
	freeing_routine(attr);
	attr->i++;
	if (all_attributes(attr->counter))
		return (attr->i);
	error_msg("There are some gibberish attributes");
	return (0);
}

void	next_iter(t_attr *attr)
{
	freeing_routine_nofd(attr);
	attr->i++;
	attr->line = get_next_line(attr->fd);
	attr->splitters = ft_split(leaktrim(attr->line, " \n"), ' ');
}

int	ending_case(t_attr *attr)
{
	freeing_routine(attr);
	error_msg("Not all attributes set");
	return (0);
}

/**
 * @brief Sets programm parameters and returns linenum where map starts
 * 
 * @param path 
 * @param data 
 */
int	set_attributes(char *path, t_cub *data)
{
	t_attr	attr;

	init_attr(&attr, path);
	while (attr.line)
	{
		if (attr_setter(&attr, "NO", &data->n_path, 1))
			;
		else if (attr_setter(&attr, "SO", &data->s_path, 10))
			;
		else if (attr_setter(&attr, "WE", &data->w_path, 100))
			;
		else if (attr_setter(&attr, "EA", &data->e_path, 1000))
			;
		else if (color_setter(&attr, "F", &data->f_col, 10000))
			;
		else if (color_setter(&attr, "C", &data->c_col, 100000))
			;
		else
		{
			if (ft_strncmp("\n", attr.line, 1))
				return (different(&attr));
		}
		next_iter(&attr);
	}
	return (ending_case(&attr));
}

void	valid_map(char *path, t_cub *data)
{
	char	**matrix;
	int		lines;

	lines = set_attributes(path, data);
	matrix = get_matrix(path, lines);
	tests(matrix);
	closed_map(matrix, data);
	data->world_map = matrix;
	set_attributes(path, data);
}
