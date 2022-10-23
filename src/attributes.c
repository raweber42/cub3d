/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:08:24 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:30:09 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_attr(t_cub	*data)
{
	data->n_path = NULL;
	data->e_path = NULL;
	data->s_path = NULL;
	data->w_path = NULL;
	data->f_col = -1;
	data->c_col = -1;
	data->i = 0;
}

void	set_textures(char **lines, t_cub *data)
{
	const char		directions[4][3] = {"NO", "EA", "SO", "WE"};
	char **const	dir_attr[4] = {&data->n_path, &data->e_path, \
	&data->s_path, &data->w_path};
	int				dir;

	while (lines[data->i])
	{
		data->splitters = ft_split(lines[data->i], ' ');
		add_all(data->splitters, data);
		dir = 0;
		while (dir < 4)
		{
			if (!ft_strncmp(directions[dir], data->splitters[0], 3))
			{
				*dir_attr[dir] = ft_strdup(data->splitters[1]);
				ft_lstadd_back(&data->free_list, ft_lstnew(*dir_attr[dir]));
			}
			dir++;
		}
		data->i++;
	}
}

void	set_colors(char **lines, t_cub *data)
{
	const char	to_color[2][2] = {"F", "C"};
	int *const	color_attr[4] = {&data->f_col, &data->c_col};
	int			col;

	data->i = 0;
	while (lines[data->i])
	{
		data->splitters = ft_split(lines[data->i], ' ');
		add_all(data->splitters, data);
		col = 0;
		while (col < 2)
		{
			if (!ft_strncmp(to_color[col], data->splitters[0], 2))
				set_couleur(color_attr[col], \
				ft_strchr(lines[data->i], ' '), data);
			col++;
		}
		data->i++;
	}
}

void	check_attributes(t_cub *data)
{
	int			i;
	const char	*directions[4] = {data->n_path, data->e_path, \
	data->s_path, data->w_path};

	i = 0;
	while (i < 4)
	{
		if (!directions[i++])
			error_msg("At least one attribute is not set", data->free_list);
	}
	if (data->f_col == -1 || data->c_col == -1)
		error_msg("Either the 'F' or 'C' attribute is not set", \
		data->free_list);
}
