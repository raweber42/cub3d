/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/25 09:45:11 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg) // sicherstellen, dass immer gefreed wird, falls nötig!
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

static int	allowed_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

void	tests(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		while(matrix[i][j])
		{
			if (matrix[i][j] == ' ')
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

void	closed_map(char **matrix)
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

void	valid_map(char *path)
{
	char	**matrix;

	matrix = get_matrix(path);
	tests(matrix);
	closed_map(matrix);
	exit(0);
}
