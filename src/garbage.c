/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:20:16 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:30:38 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_garbage_helper(char *line, char **splitters, t_cub *data)
{
	const char		attributes[6][3] = {"NO", "EA", "SO", "WE", "F", "C"};
	int				attr;

	attr = 0;
	while (attr < 6)
	{
		if (attr < 4 && !ft_strncmp(attributes[attr], splitters[0], 3))
			return (0);
		else if (attr < 6 && !ft_strncmp(attributes[attr], splitters[0], 2))
			return (0);
		attr++;
	}
	if ((!space_str(line) && line[0]) \
		&& line < data->world_map[0])
	{
		return (1);
	}
	return (0);
}

void	check_garbage(char **lines, t_cub *data)
{
	data->i = 0;
	while (lines[data->i])
	{
		data->splitters = ft_split(lines[data->i], ' ');
		add_all(data->splitters, data);
		if (check_garbage_helper(lines[data->i], data->splitters, data))
			error_msg("There is garbage in the config", data->free_list);
		data->i++;
	}
}
