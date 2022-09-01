/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:22:41 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 11:50:32 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_counter(t_attr *attr, int inc, char *value)
{
	int	i;
	int	copy;

	attr->counter += inc;
	copy = attr->counter;
	i = 1;
	while (copy / i)
	{
		if ((copy / i) % 10 > 1)
		{
			if (value)
				free(value);
			freeing_routine(attr);
			error_msg("An attribute is set several times");//Leakfree
		}
		i *= 10;
	}
}

void	init_attr(t_attr *attr, char *path, t_cub *data)
{
	char	*to_free;

	attr->splitters = NULL;
	attr->splitters2 = NULL;
	attr->line = NULL;
	data->n_path = NULL;
	data->s_path = NULL;
	data->w_path = NULL;
	data->e_path = NULL;
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
	if (!ft_strncmp(ident, attr->splitters[0], ft_strlen(ident) + 1))
	{
		free(to_free);
		wrong_number(attr);
		set_counter(attr, mag, *to_set);
		*to_set = ft_strtrim(ft_strdup(attr->splitters[1]), "\n");
		return (1);
	}
	free(to_free);
	return (0);
}

unsigned char	fancy_atoi(char *str)
{
	char			*to_free;
	unsigned char	c;

	to_free = leaktrim(str, "\n ,");
	c = (unsigned char)ft_atoi(to_free);
	free(to_free);
	return (c);
}

int	color_setter(t_attr *attr, char *ident, int *to_set, int mag)
{
	if (!ft_strncmp(ident, attr->splitters[0], ft_strlen(ident) + 1))
	{
		attr->to_free = ft_strjoin(ident, " ");
		attr->to_free2 = leaktrim(attr->line, attr->to_free);
		attr->splitters2 = ft_split(attr->to_free2, ',');
		free(attr->to_free);
		free(attr->to_free2);
		if (ft_rstrstrlen(attr->splitters2) < 3)
		{
			freeing_routine(attr);
			error_msg("You have not defined all color elements\n");//Leakfree
		}
		else if (ft_rstrstrlen(attr->splitters2) > 3)
		{
			freeing_routine(attr);
			error_msg("Too many color arguments");//Leafree
		}
		printf("THIS IS THE FANCY: %d\n", fancy_atoi(attr->splitters2[0]));
		*to_set = rgb_to_int(fancy_atoi(attr->splitters2[0]), \
		fancy_atoi(attr->splitters2[1]), fancy_atoi(attr->splitters2[2]));
		set_counter(attr, mag, NULL);
		return (1);
	}
	return (0);
}
