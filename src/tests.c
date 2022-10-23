/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:14:54 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:25:08 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	if_nsurrounded(char **map, int i, int j, t_cub *data)
{
	if (map[i][j] == ' ')
	{
		if (!surounded(map, i, j, -1))
			error_msg("Internal space not surrounded by ones", data->free_list);
	}
}

void	map_closed(char **map, t_cub *data)
{
	t_closed	input;

	input.i = 0;
	input.limit = 0;
	while (map[0][input.limit] != '1')
		input.limit++;
	input.ulimit = ft_strlen(map[0]);
	while (map[0][input.ulimit] != '1')
		input.ulimit--;
	recursive_closed(map, input, data);
}

void	test_characters(t_cub *data)
{
	int				i;
	t_charfun const	tests[2] = {if_wrong_char, playernum_caller};

	i = 0;
	while (i < 2)
	{
		all_chars(data->world_map, tests[i], data);
		i++;
	}
	if (playernum(0, data))
		error_msg("Invalid number of players", data->free_list);
}

void	test_coordinates(t_cub *data)
{
	int				i;
	t_coorfun const	tests[3] = {if_0sourrounded, set_player, if_nsurrounded};

	i = 0;
	while (i < 3)
	{
		all_chars2(data->world_map, tests[i], data);
		i++;
	}
}
