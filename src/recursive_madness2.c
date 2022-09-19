/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_madness2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:19:04 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/19 11:51:11 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	int				iter;
	const t_rec_fun	fun_arr[5] = \
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
