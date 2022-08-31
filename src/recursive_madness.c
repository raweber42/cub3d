/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_madness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:51:13 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 19:11:22 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	right_one(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1])
		return (0);
	if (matrix[i][j + 1] == '1')
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	else
		return (right_one(matrix, i, j + 1));
}

int	left_one(char **matrix, int i, int j)
{
	if (j == 0)
		return (0);
	if (matrix[i][j - 1] == '1')
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	else
		return (left_one(matrix, i, j - 1));
}

int	allowed_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' \
	|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	left_border(char **matrix, int i, int j)
{
	if (j == 0)
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	return (left_border(matrix, i, j - 1));
}

int	right_border(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1])
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	return (right_border(matrix, i, j + 1));
}

int	surounded(char **matrix, int i, int j, int callback)
{
	int				iter;
	const rec_fun	fun_arr[5] = \
	{closed_left, closed_up, closed_right, closed_down};

	iter = 0;
	while (iter < 4)
	{
		if (callback == iter)
		{
			iter++;
			continue ;
		}
		if (!fun_arr[iter](matrix, i, j))
			return (0);
		iter++;
	}
	return (1);
}
