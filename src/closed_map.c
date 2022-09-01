/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:05:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 14:25:23 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_closed(t_closed *closed)
{
	closed->i = 0;
	closed->j = 0;
	closed->player = 0;
}

void	set_player(t_closed *closed, t_cub *data, char **matrix)
{
	if (matrix[closed->i][closed->j] == 'N' || \
		matrix[closed->i][closed->j] == 'E' || \
		matrix[closed->i][closed->j] == 'W' || \
		matrix[closed->i][closed->j] == 'S')
	{
		data->pos.x = closed->i;
		data->pos.y = closed->j;
		data->orientation = matrix[closed->i][closed->j];
		matrix[closed->i][closed->j] = '0';
		if (closed->player == 1)
			error_msg("You have to play alone", data, matrix);
		closed->player = 1;
	}
}

void	set_limits(char **matrix, t_closed *closed)
{
	if (closed->i > 0)
		closed->limit = ft_strlen(matrix[closed->i - 1]);
	if (matrix[closed->i + 1])
		closed->ulimit = ft_strlen(matrix[closed->i + 1]);
}

void	check_limits(t_closed *closed, char **matrix, t_cub *data)
{
	if (closed->i > 0 && closed->j >= closed->limit \
	&& matrix[closed->i][closed->j] != '1')
	{
		error_msg("Map is not closed", data, matrix);
	}
	if (matrix[closed->i + 1] && closed->j \
	>= closed->ulimit && matrix[closed->i][closed->j] != '1')
	{
		error_msg("Map is not closed", data, matrix);
	}
}

/**
 * @brief map closed (traps), player number
 * 
 * @param matrix 
 * @param data 
 */
void	closed_map(char **matrix, t_cub *data)
{
	t_closed	closed;

	init_closed(&closed);
	while (matrix[closed.i])
	{
		set_limits(matrix, &closed);
		while (matrix[closed.i][closed.j])
		{
			if (matrix[closed.i][closed.j] == ' ')
			{
				closed.j++;
				continue ;
			}
			check_limits(&closed, matrix, data);
			set_player(&closed, data, matrix);
			closed.j++;
		}
		closed.j = 0;
		closed.i++;
	}
	(void) data;
	if (closed.player == 0)
		error_msg("No player set in map", data, matrix);
}
