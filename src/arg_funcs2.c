/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:49:10 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 13:04:01 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	playernum(char c, t_cub	*data)
{
	static int		one_player = 0;
	const char		set[5] = "NESW";
	int				i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			data->orientation = c;
			one_player++;
		}
		i++;
	}
	if (one_player == 1)
		return (0);
	return (1);
}

void	playernum_caller(char c, t_cub	*data)
{
	playernum(c, data);
}

void	set_player(char **str, int i, int j, t_cub *data)
{
	const char	set[5] = "NESW";
	int			k;

	k = 0;
	while (set[k])
	{
		if (str[i][j] == set[k])
		{
			data->pos.x = i + 0.5;
			data->pos.y = j + 0.5;
			str[i][j] = '0';
		}
		k++;
	}
}
