/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _2Dimensions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:01:14 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/20 18:06:04 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**_2dalloc(char *all)
{
	char	**lines;
	int		nb_linebr;
	int		i;

	nb_linebr = 0;
	i = 0;
	while (all[i])
	{
		if (all[i++] == '\n')
			nb_linebr++;
	}
	nb_linebr++;
	lines = ft_calloc(nb_linebr + 1, sizeof(char *));
	lines[0] = &all[0];
	lines[nb_linebr] = NULL;
	return (lines);
}

void	shallow_copy(char **lines, char *all)
{
	int	i;
	int	elem;

	elem = 0;
	i = 0;
	while (all[i])
	{
		if (all[i++] == '\n')
		{
			all[i - 1] = '\0';
			lines[++elem] = &all[i];
		}
	}
}

void	shift_space_lines(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = i;
		if (space_str(lines[i]))
		{
			while (lines[j])
			{
				lines[j] = lines[j + 1];
				j++;
			}
		}
		i++;
	}
}
