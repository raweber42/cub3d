/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:05:16 by raweber           #+#    #+#             */
/*   Updated: 2022/08/26 09:52:57 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// helper for allocating the wall (=texture) structs
int	allocate_walls(t_cub *data)
{
	data->n_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->n_wall)
		return (1);
	data->s_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->s_wall)
		return (1);
	data->e_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->e_wall)
		return (1);
	data->w_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->w_wall)
		return (1);
	return (0);
}

//  initializes view according to orientation of player
void	set_view_direction(t_cub *data)
{
	if (data->orientation == 'W')
	{
		data->dir.x = 0;
		data->dir.y = -1;
	}
	else if (data->orientation == 'S')
	{
		data->dir.x = 1;
		data->dir.y = 0;
	}
	else if (data->orientation == 'E')
	{
		data->dir.x = 0;
		data->dir.y = 1;
	}
	else
	{
		data->dir.x = -1;
		data->dir.y = 0;
	}
}

// converts the four RGBA values to a single integer using bitshifting
int	rgba_to_int(t_color col)
{
	return (col.alpha << 24 | col.red << 16 | col.green << 8 | col.blue);
}

// checks, if there exists an mlx image already and destroys it and
// generates a new one if so
void	mlx_image_reload(t_cub *data)
{
	if (data->mlx_data->mlx_img)
	{
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
		data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx_ptr, \
				data->mlx_data->win_width, data->mlx_data->win_height);
	}
	if (data->n_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->n_wall->mlx_img);
	if (data->s_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->s_wall->mlx_img);
	if (data->e_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->e_wall->mlx_img);
	if (data->w_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->w_wall->mlx_img);
	destroy_wall(data->n_wall);
	destroy_wall(data->s_wall);
	destroy_wall(data->e_wall);
	destroy_wall(data->w_wall);
}
