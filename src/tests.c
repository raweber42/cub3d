/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:52:32 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 19:07:56 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_space(char **matrix, int i, int j)
{
	if (matrix[i][j] == ' ')
	{
		if (left_border(matrix, i, j) && right_one(matrix, i, j))
			return (1);
		else if (right_border(matrix, i, j) && left_one(matrix, i, j))
			return (1);
		if (right_border(matrix, i, j) || left_border(matrix, i, j))
		{
			free_all(matrix);
			error_msg("Map is not surrounded by ones");
		}
		if (surounded(matrix, i, j, -1))
			return (1);
		{
			free_all(matrix);
			error_msg("Map contains spaces");
		}
	}
	return (0);
}

void	two_tests(char **matrix, int i, int j)
{
	if (!allowed_char(matrix[i][j]))
	{
		free_all(matrix);
		error_msg("Map contains invalid character");
	}
	if ((i == 0 && matrix[i][j] != '1') \
		|| (!matrix[i + 1] && matrix[i][j] != '1')
		|| (j == 0 && matrix[i][j] != '1')
		|| (!matrix[i][j + 1] && matrix[i][j] != '1'))
	{
		free_all(matrix);
		error_msg("Map not surrounded by ones");
	}
}

/**
 * @brief spaces, surrounded by ones, invalid chars
 * 
 * @param matrix 
 * @param data 
 */
void	tests(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		while (matrix[i][j])
		{
			if (valid_space(matrix, i, j))
			{
				j++;
				continue ;
			}
			two_tests(matrix, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}
