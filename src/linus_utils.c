/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:23:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/20 18:12:34 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**reverse_map(t_cub *data)
{
	char	**reversed_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	reversed_map = calloc(ft_strstrlen(data->world_map) + 1, sizeof(char *));
	while (data->world_map[i])
		i++;
	reversed_map[i--] = NULL;
	while (i >= 0)
		reversed_map[j++] = data->world_map[i--];
	return (reversed_map);
}

void	all_chars(char **strstr, t_charfun toApply, t_cub *data)
{
	int	i;
	int	j;

	if (!strstr)
		return ;
	i = 0;
	while (strstr[i])
	{
		j = 0;
		while (strstr[i][j])
		{
			toApply(strstr[i][j], data);
			j++;
		}
		i++;
	}
}

// Overload with coordinate functions
void	all_chars2(char **strstr, t_coorfun toApply, t_cub *data)
{
	int	i;
	int	j;

	if (!strstr)
		return ;
	i = 0;
	while (strstr[i])
	{
		j = 0;
		while (strstr[i][j])
		{
			toApply(strstr, i, j, data);
			j++;
		}
		i++;
	}
}

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters && splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	if (splitters)
		free(splitters);
}
