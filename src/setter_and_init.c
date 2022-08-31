/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:22:41 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 17:52:19 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_counter(t_attr *attr, int inc)
{
	int	i;
	int	copy;

	attr->counter += inc;
	copy = attr->counter;
	i = 1;
	while (copy / i)
	{
		if (copy % 10 > 1)
		{
			freeing_routine(attr);
			error_msg("An attribute is set several times");
		}
		i *= 10;
	}
}

void	init_attr(t_attr *attr, char *path)
{
	char	*to_free;

	attr->splitters = NULL;
	attr->splitters2 = NULL;
	attr->line = NULL;
	attr->i = 0;
	attr->fd = open(path, O_RDONLY);
	attr->counter = 0;
	attr->line = get_next_line(attr->fd);
	to_free = leaktrim(attr->line, " \n");
	attr->splitters = ft_split(to_free, ' ');
	free(to_free);
}

int	attr_setter(t_attr	*attr, char *ident, char **to_set, int mag)
{
	char	*to_free;

	to_free = leaktrim(attr->splitters[0], " ");
	if (!ft_strncmp(ident, to_free, ft_strlen(ident) + 1))
	{
		free(to_free);
		wrong_number(attr);
		*to_set = ft_strtrim(ft_strdup(attr->splitters[1]), "\n");
		set_counter(attr, mag);
		return (1);
	}
	free(to_free);
	return (0);
}

unsigned char	fancy_atoi(char *str)
{
	char	*to_free;

	to_free = leaktrim(str, "\n ,");
	return ((unsigned char)ft_atoi(to_free));
	free(to_free);
}

int	color_setter(t_attr *attr, char *ident, int *to_set, int mag)
{
	char	*to_free;

	if (!ft_strncmp(ident, attr->splitters[0], ft_strlen(ident) + 1))
	{
		to_free = ft_strjoin(ident, " ");
		attr->splitters2 = ft_split(leaktrim(attr->line, to_free), ',');
		free(to_free);
		if (ft_strstrlen(attr->splitters2) < 3)
		{
			freeing_routine(attr);
			error_msg("You have not defined all color elements\n");
		}
		else if (ft_strstrlen(attr->splitters2) > 3)
		{
			freeing_routine(attr);
			error_msg("Too many color arguments");
		}
		*to_set = rgb_to_int(fancy_atoi(attr->splitters2[1]), \
		fancy_atoi(attr->splitters2[2]), \
		fancy_atoi(attr->splitters2[3]));
		set_counter(attr, mag);
		return (1);
	}
	return (0);
}
