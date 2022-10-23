/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:19:27 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:25:08 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	add_all(char **splitters, t_cub *data)
{
	int	i;

	i = 0;
	ft_lstadd_back(&data->free_list, ft_lstnew(splitters));
	while (splitters[i])
	{
		ft_lstadd_back(&data->free_list, ft_lstnew(splitters[i]));
		i++;
	}
}

void	parsing(t_cub *data, char **av)
{
	char	*trimmed_all;
	char	**lines;

	trimmed_all = file_trimmed(av, data);
	lines = _2dimensions(trimmed_all, data);
	init_attr(data);
	set_textures(lines, data);
	set_colors(lines, data);
	check_attributes(data);
	set_world_map(data, lines);
	check_garbage(lines, data);
	test_characters(data);
	test_coordinates(data);
	map_closed(data->world_map, data);
	data->r_map = reverse_map(data);
	map_closed(data->r_map, data);
	free_(data->r_map);
}
