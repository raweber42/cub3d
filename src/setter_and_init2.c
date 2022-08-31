/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_and_init2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:57:52 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 17:15:46 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_fm(t_fm *fm, char *path, int elem)
{
	fm->fd = open(path, O_RDONLY);
	fm->i = 1;
	while (fm->i < elem)
	{
		free(get_next_line(fm->fd));
		fm->i++;
	}
	fm->i = 0;
	fm->j = 0;
	fm->line = get_next_line(fm->fd);
}

void	init_go_map(t_gelem *gelem, char *path, int elem)
{
	gelem->fd = open(path, O_RDONLY);
	gelem->i = 1;
	while (gelem->i < elem)
	{
		free(get_next_line(gelem->fd));
		gelem->i++;
	}
	gelem->line = get_next_line(gelem->fd);
	gelem->max_l = 0;
	gelem->i = 1;
}
