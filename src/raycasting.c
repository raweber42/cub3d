/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/09/19 11:48:30 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// calculates height of line to draw on screen, colorizes it accordingly
// and fills bottom and top with floor- and ceiling-color
void	draw_pixels(t_cub *data, int x)
{
	double	wall_x;
	int		tex_x;

	if (data->side_hit == 0)
		wall_x = data->pos.y + data->perp_wall_dist * data->ray_dir.y;
	else
		wall_x = data->pos.x + data->perp_wall_dist * data->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEXWIDTH);
	if (data->side_hit == 0 && data->ray_dir.x > 0)
		tex_x = TEXWIDTH - tex_x - 1;
	if (data->side_hit == 1 && data->ray_dir.y < 0)
		tex_x = TEXWIDTH - tex_x - 1;
	put_all_pixels(data, tex_x, x);
}

// helper for calculating the steps taken by the player
void	set_step_xy(t_cub *data, int *step_x, int *step_y)
{
	if (data->ray_dir.x < 0)
	{
		*step_x = -1;
		data->side_dist.x = (data->pos.x - data->map_x) * data->delta_dist.x;
	}
	else
	{
		*step_x = 1;
		data->side_dist.x = (data->map_x + 1.0 - data->pos.x) \
			* data->delta_dist.x;
	}
	if (data->ray_dir.y < 0)
	{
		*step_y = -1;
		data->side_dist.y = (data->pos.y - data->map_y) * data->delta_dist.y;
	}
	else
	{
		*step_y = 1;
		data->side_dist.y = (data->map_y + 1.0 - data->pos.y) \
			* data->delta_dist.y;
	}
}

//calculates ray position and direction
void	set_rays(t_cub *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREENWIDTH - 1;
	data->ray_dir.x = data->dir.x + data->plane.x * camera_x;
	data->ray_dir.y = data->dir.y + data->plane.y * camera_x;
	data->map_x = (int)data->pos.x;
	data->map_y = (int)data->pos.y;
	if (data->ray_dir.x == 0)
		data->delta_dist.x = 1e30;
	else
		data->delta_dist.x = fabs(1 / data->ray_dir.x);
	if (data->ray_dir.y == 0)
		data->delta_dist.y = 1e30;
	else
		data->delta_dist.y = fabs(1 / data->ray_dir.y);
}

// starts the ray calculations and performs dda (jumping to next square, either
// in x- or y- direction) until it hits a wall to find which square to move to
void	handle_rays_and_dda(t_cub *data, int x)
{
	int		step_x;
	int		step_y;
	int		hit;

	set_rays(data, x);
	set_step_xy(data, &step_x, &step_y);
	hit = 0;
	while (hit == 0)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_dist.x;
			data->map_x += step_x;
			data->side_hit = 0;
		}
		else
		{
			data->side_dist.y += data->delta_dist.y;
			data->map_y += step_y;
			data->side_hit = 1;
		}
		if (data->world_map[data->map_x][data->map_y] == 49)
			hit = 1;
	}
}

// main function for raycasting
int	raycasting(t_cub *data)
{
	int	x;

	x = 0;
	mlx_image_reload(data);
	handle_textures(data);
	while (x < SCREENWIDTH)
	{
		handle_rays_and_dda(data, x);
		if (data->side_hit == 0)
			data->perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
		else
			data->perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
		draw_pixels(data, x++);
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr,
		data->mlx_data->mlx_img, 0, 0);
	return (0);
}
