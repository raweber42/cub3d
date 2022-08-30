/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_madness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:51:13 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/30 21:56:37 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	allowed_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	valid_left(char **matrix, int i, int j)
{
	if (j == 0)
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	return (valid_left(matrix, i, j - 1));
}

int	valid_right(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1])
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	return (valid_right(matrix, i, j + 1));
}

int	closed_left(char **matrix, int i, int j)
{
	if (j == 0 || matrix[i][j - 1] == '1')
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	else
		return (1);
}

int	closed_up(char **matrix, int i, int j)
{
	if (i == 0 || matrix[i - 1][j] == '1')
		return (1);
	else if (matrix[i - 1][j] != ' ')
		return (0);
	else
		return (1);
}

int	closed_right(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1] || matrix[i][j + 1] == '1')
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	else
		return (surounded(matrix, i, j + 1, 0));
}

int	closed_down(char **matrix, int i, int j)
{
	if (!matrix[i + 1] || matrix[i + 1][j] == '1')
		return (1);
	else if (matrix[i + 1][j] != ' ')
		return (0);
	else
		return (surounded(matrix, i + 1, j, 1));
}

int	surounded(char **matrix, int i, int j, int callback)
{
	int	iter;
	const rec_fun	fun_arr[5] = {closed_left, closed_up, closed_right, closed_down};

	iter = 0;
	while (iter < 4)
	{
		if (callback == iter)
		{
			iter++;
			continue;
		}
		if (!fun_arr[iter](matrix, i, j))
			return (0);
		iter++;
	}
	return (1);
}
