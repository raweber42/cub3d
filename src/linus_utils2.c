/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:38:29 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 17:25:08 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	free_and_return(char *trimmed_line)
{
	free_(trimmed_line);
	return (1);
}

void	error_msg(char *msg, t_list *allocated)
{
	if (allocated)
		ft_lstclear(&allocated, free_);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

int	to_rgb(char *r, char *g, char *b, t_cub *for_free)
{
	int			rgb;
	int			converted;
	const char	*colors[4] = {b, g, r};
	char		*sucess;
	int			i;

	rgb = 0;
	i = 0;
	while (colors[i])
	{
		converted = strtol(colors[i], &sucess, 10);
		if (*sucess || (converted > 255 \
		|| converted < 0))
			error_msg("'F' and/or 'C' attribute value invalid", \
			for_free->free_list);
		rgb += converted << (i * 8);
		i++;
	}
	return (rgb);
}

void	set_couleur(int *attr, char *value, t_cub *for_free)
{
	char	**splitters;
	char	*tmp;
	int		i;

	if (!value)
		error_msg("No value to 'F' and/or 'C' attribute", for_free->free_list);
	splitters = ft_split(value, ',');
	if (ft_strstrlen(splitters) != 3)
		error_msg("Invalid number of values to 'F' and/or 'C' attribute", \
		for_free->free_list);
	i = 0;
	while (splitters[i])
	{
		tmp = ft_strtrim(splitters[i], " ");
		splitters[i] = tmp;
		i++;
	}
	*attr = to_rgb(splitters[0], splitters[1], splitters[2], for_free);
	free_all(splitters);
}

int	space_str(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
