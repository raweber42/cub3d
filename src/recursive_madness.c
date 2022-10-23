/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_madness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:35:50 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:25:08 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_closed	new_limits(char **map, t_closed old)
{
	t_closed	new;

	new.limit = 0;
	while (map[old.i][new.limit] != '1')
		new.limit++;
	new.ulimit = ft_strlen(map[old.i]) - 1;
	while (map[old.i][new.ulimit] != '1')
		new.ulimit--;
	new.i = old.i + 1;
	return (new);
}

static t_closed	zero_limits(char **map, t_closed old)
{
	t_closed	zero;

	zero.limit = 0;
	while (map[old.i][zero.limit] && map[old.i][zero.limit] != '0')
		zero.limit++;
	zero.ulimit = ft_strlen(map[old.i]) - 1;
	while (zero.ulimit > 0 && map[old.i][zero.ulimit] != '0')
		zero.ulimit--;
	return (zero);
}

// limit = lower limit, ulimit = upper limit
void	recursive_closed(char **map, t_closed old, t_cub *data)
{
	t_closed	new;
	t_closed	zero;

	if (!map[old.i])
		return ;
	new = new_limits(map, old);
	zero = zero_limits(map, old);
	if (!map[old.i][zero.limit])
	{
		zero.limit = -5;
		return (recursive_closed(map, new, data));
	}
	if (zero.limit < old.limit)
		error_msg("Map is not closed", data->free_list);
	if (zero.ulimit > old.ulimit)
		error_msg("Map is not closed", data->free_list);
	return (recursive_closed(map, new, data));
}
