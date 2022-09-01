/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:22:41 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 14:31:52 by ljahn            ###   ########.fr       */
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
		if ((copy / i) % 10 > 1)
		{		
			freeing_routine(attr);
			error_msg("An attribute is set several times", attr->data, NULL);
		}
		i *= 10;
	}
}

int	attr_setter(t_attr	*attr, char *ident, char **to_set, int mag)
{
	char	*to_free;

	to_free = leaktrim(attr->splitters[0], " ");
	if (!ft_strncmp(ident, attr->splitters[0], ft_strlen(ident) + 1))
	{
		free(to_free);
		wrong_number(attr, attr->data);
		set_counter(attr, mag);
		*to_set = ft_strtrim(ft_strdup(attr->splitters[1]), "\n");
		return (1);
	}
	free(to_free);
	return (0);
}

void	not_numeric(char *str, t_attr *attr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			free(str);
			error_msg("Color component is not a pure number", attr->data, NULL);
		}
		i++;
	}
}

unsigned char	fancy_atoi(t_attr *attr, int of)
{
	char			*to_free;
	unsigned char	c;

	to_free = leaktrim(attr->splitters2[of], "\n ,");
	not_numeric(to_free, attr);
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
			error_msg("You have not defined all color elements\n", \
				attr->data, NULL);
		}
		else if (ft_rstrstrlen(attr->splitters2) > 3)
		{
			freeing_routine(attr);
			error_msg("Too many color arguments", attr->data, NULL);
		}
		*to_set = rgb_to_int(fancy_atoi(attr, 0), \
		fancy_atoi(attr, 1), fancy_atoi(attr, 2));
		set_counter(attr, mag);
		return (1);
	}
	return (0);
}
