/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_init2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:57:52 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 12:19:17 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_fm(t_fm *fm, char *path, int elem)
{
	fm->fd = open(path, O_RDONLY);
	fm->i = 1;
	while (fm->i < elem)
	{
		free(get_next_line(fm->fd));
		fm->i++;
	}
	fm->i = 0;
	fm->j = 0;
	fm->line = get_next_line(fm->fd);
}

void	init_go_map(t_gelem *gelem, char *path, int elem)
{
	gelem->fd = open(path, O_RDONLY);
	gelem->i = 1;
	while (gelem->i < elem)
	{
		free(get_next_line(gelem->fd));
		gelem->i++;
	}
	gelem->line = get_next_line(gelem->fd);
	gelem->max_l = 0;
	gelem->i = 1;
}

/**
 * @brief Sets programm parameters and returns linenum where map starts
 * 
 * @param path 
 * @param data 
 */
int	set_attributes(t_cub *data, t_attr attr)
{
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
			if (ft_strncmp("\n", attr.line, 1) && ft_nasp(attr.line))
				return (different(&attr, data));
		}
		next_iter(&attr);
	}
	return (ending_case(&attr, data));
}
