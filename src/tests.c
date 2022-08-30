/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:52:32 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/30 22:01:16 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_space(char **matrix, int i, int j)
{
	if (matrix[i][j] == ' ')
	{
		if (valid_left(matrix, i, j) || valid_right(matrix, i, j))
			return (1);
		if (surounded(matrix, i, j, -1))
			return (1);
		error_msg("Map contains spaces");
	}
	return (0);
}

/**
 * @brief spaces, surrounded by ones, invalid chars
 * 
 * @param matrix 
 * @param data 
 */
void	tests(char **matrix, t_cub *data)
{
	int	i;
	int	j;

	(void)data;
	i = 0;
	j = 0;
	while (matrix[i])
	{
		while(matrix[i][j])
		{
			if (valid_space(matrix, i, j))
			{
				j++;
				continue ;
			}
			if (!allowed_char(matrix[i][j]))
				error_msg("Map contains invalid character");
			if ((i == 0 && matrix[i][j] != '1') \
				|| (!matrix[i + 1] && matrix[i][j] != '1')
				|| (j == 0 && matrix[i][j] != '1')
				|| (!matrix[i][j + 1] && matrix[i][j] != '1'))
				error_msg("Map not surrounded by ones");
			j++;
		}
		j = 0;
		i++;
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
	int	i;
	int	j;
	int	player;
	int	limit;
	int	ulimit;

	i = 0;
	j = 0;
	player = 0;
	while (matrix[i])
	{
		if (i > 0)
			limit = ft_strlen(matrix[i - 1]);
		if (matrix[i + 1])
			ulimit = ft_strlen(matrix[i  + 1]);
		while(matrix[i][j])
		{
			if (matrix[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (i > 0 && j >= limit && matrix[i][j] != '1')
				error_msg("Map is not closed");
			if (matrix[i + 1] && j >= ulimit && matrix[i][j] != '1')
				error_msg("Map is not closed");
			if (matrix[i][j] == 'N' || \
				matrix[i][j] == 'E' || \
				matrix[i][j] == 'W' || \
				matrix[i][j] == 'S')
			{
				data->pos.x = i;
				data->pos.y = j;
				data->orientation = matrix[i][j];
				matrix[i][j] = '0';
				if (player == 1)
					error_msg("This is not coop");
				player = 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player == 0)
		error_msg("You are not that lonley");
}
