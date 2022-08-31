/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_madness2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:19:04 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 17:19:18 by ljahn            ###   ########.fr       */
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
