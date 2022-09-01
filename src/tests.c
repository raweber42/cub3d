/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:52:32 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 14:23:53 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_space(char **matrix, int i, int j, t_cub *data)
{
	if (matrix[i][j] == ' ')
	{
		if (left_border(matrix, i, j) && right_one(matrix, i, j))
			return (1);
		else if (right_border(matrix, i, j) && left_one(matrix, i, j))
			return (1);
		if (right_border(matrix, i, j) || left_border(matrix, i, j))
			error_msg("Map is not surrounded by ones", data, matrix);
		if (surounded(matrix, i, j, -1))
			return (1);
		else
			error_msg("Map contains spaces", data, matrix);
	}
	return (0);
}

void	two_tests(char **matrix, int i, int j, t_cub *data)
{
	if (!allowed_char(matrix[i][j]))
		error_msg("Map contains invalid character", data, matrix);
	if ((i == 0 && matrix[i][j] != '1') \
		|| (!matrix[i + 1] && matrix[i][j] != '1')
		|| (j == 0 && matrix[i][j] != '1')
		|| (!matrix[i][j + 1] && matrix[i][j] != '1'))
	{
		error_msg("Map not surrounded by ones", data, matrix);
	}
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

	i = 0;
	j = 0;
	while (matrix[i])
	{
		while (matrix[i][j])
		{
			if (valid_space(matrix, i, j, data))
			{
				j++;
				continue ;
			}
			two_tests(matrix, i, j, data);
			j++;
		}
		j = 0;
		i++;
	}
}
