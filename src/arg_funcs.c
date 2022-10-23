/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:42:37 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:25:08 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Does the free need to be protected in invalid matrix case?
static int	_0_sourrounded(char **matrix, int i, int j)
{
	char	*trimmed_line;

	trimmed_line = leaktrim(matrix[i], " ");
	if ((!matrix[i + 1] || i == 0) && j < ft_strlen(trimmed_line))
	{
		if (trimmed_line[j] != '1')
			return (free_and_return(trimmed_line));
	}
	if (j == 0)
	{
		if (trimmed_line[ft_strlen(trimmed_line) - 1] != '1')
			return (free_and_return(trimmed_line));
		if (trimmed_line[0] != '1')
			return (free_and_return(trimmed_line));
	}
	free_(trimmed_line);
	return (0);
}

void	if_0sourrounded(char **matrix, int i, int j, t_cub *data)
{
	if (_0_sourrounded(matrix, i, j))
		error_msg("Map is not sourrounded by ones", data->free_list);
}

static int	wrong_char(char c)
{
	int			allowed;
	const char	set[8] = " 01NOSWE";

	allowed = 0;
	while (set[allowed])
	{
		if (c == set[allowed])
			return (0);
		allowed++;
	}
	return (1);
}

void	if_wrong_char(char c, t_cub	*data)
{
	(void)data;
	if (wrong_char(c))
		error_msg("Map contains invalid characters", data->free_list);
}
