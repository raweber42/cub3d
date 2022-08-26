/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/26 09:35:12 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// calculates height of line to draw on screen, colorizes it accordingly
// and fills bottom and top with floor- and ceiling-color
void	draw_pixels(t_cub *data, int x)
{
	int	i;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	line_height = (int)(screenHeight / data->perp_wall_dist);
	if (data->perp_wall_dist == 0)
		line_height = (double) screenHeight;
	// printf("line_height: %d\n", line_height);
	draw_start = -line_height / 2 + screenHeight / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + screenHeight / 2;
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	// printf("drawend = %d\nperp_wall_dist = %f\nline_height = %d\n\n", draw_end, data->perp_wall_dist, line_height);
	// sleep(1);
	// FROM HERE ON IT DIFFERS!
	// calculate X coordinate where wall was hit
	double	wallX;
	if (data->side_hit == 0)
		wallX = data->pos.y + data->perp_wall_dist * data->ray_dir.y;
	else
		wallX = data->pos.x + data->perp_wall_dist * data->ray_dir.x;
	wallX -= floor(wallX);

	// calculate x coordinate of texture
	int	texX = (int)(wallX * (double)TEXWIDTH);
	if (data->side_hit == 0 && data->ray_dir.x > 0)
		texX = TEXWIDTH - texX - 1;
	if (data->side_hit == 1 && data->ray_dir.y < 0)
		texX = TEXWIDTH - texX - 1;
	// last step
	double	step = (double) TEXHEIGHT / (double) line_height; // check line_height
	double	texPos = (draw_start - screenHeight / 2 + line_height / 2) * step;  // is mapheight right?
	for (int y = draw_start; y < draw_end; y++)
	{
		int texY = (int)texPos;// & (TEXHEIGHT - 1); // needed?
		texPos += step;
		if (data->side_hit == 0 && data->ray_dir.x > 0)
			color = rgba_to_int(*(data->s_wall->matrix[texY][texX]));
		else if (data->side_hit == 0 && data->ray_dir.x < 0)
			color = rgba_to_int(*(data->n_wall->matrix[texY][texX]));
		else if (data->side_hit == 1 && data->ray_dir.y < 0)
			color = rgba_to_int(*(data->w_wall->matrix[texY][texX]));
		else if (data->side_hit == 1 && data->ray_dir.y > 0)
			color = rgba_to_int(*(data->e_wall->matrix[texY][texX]));
		
		// printf("texY: %d\n", texY);
		// printf("texY: %d\n", line_height);
		// printf("current color: %d\n", rgba_to_int(*(data->n_wall->matrix[texY][texX])));
		// for (int z = 0; z < line_height/TEXHEIGHT; z++)
		my_mlx_pixel_put(data->mlx_data, x, y, color);
	}


		
	// color = get_color(data, data->mapX, data->mapY); // only for untextured



	i = 0;
	while (i < draw_start)
		my_mlx_pixel_put(data->mlx_data, x, i++, data->c_col);
	// while (i < draw_end)
	// 	my_mlx_pixel_put(data->mlx_data, x, i++, color);
	i = draw_end;
	while (i < screenHeight)
	{	
		my_mlx_pixel_put(data->mlx_data, x, i++, data->f_col);
	}
}

void	set_step_xy(t_cub *data, int *step_x, int *step_y)
{
	if (data->ray_dir.x < 0)
	{
		*step_x = -1;
		data->side_dist.x = (data->pos.x - data->mapX) * data->delta_dist.x;
	}
	else
	{
		*step_x = 1;
		data->side_dist.x = (data->mapX + 1.0 - data->pos.x) \
			* data->delta_dist.x;
	}
	if (data->ray_dir.y < 0)
	{
		*step_y = -1;
		data->side_dist.y = (data->pos.y - data->mapY) * data->delta_dist.y;
	}
	else
	{
		*step_y = 1;
		data->side_dist.y = (data->mapY + 1.0 - data->pos.y) \
			* data->delta_dist.y;
	}
}

//calculates ray position and direction
void	set_rays(t_cub *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)screenWidth - 1;
	data->ray_dir.x = data->dir.x + data->plane.x * camera_x;
	data->ray_dir.y = data->dir.y + data->plane.y * camera_x;
	data->mapX = (int)data->pos.x;
	data->mapY = (int)data->pos.y;
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
			data->mapX += step_x;
			data->side_hit = 0;
		}
		else
		{
			data->side_dist.y += data->delta_dist.y;
			data->mapY += step_y;
			data->side_hit = 1;
		}
		if (worldMap[data->mapX][data->mapY] == 1)
			hit = 1;
	}
}

int	raycasting(t_cub *data)
{
	int	x;

	x = 0;
	mlx_image_reload(data);
	handle_textures(data);
	while (x < screenWidth)
	{
		handle_rays_and_dda(data, x);
		if (data->side_hit == 0)
			data->perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
		else
			data->perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
		
		draw_pixels(data, x++);
		// if (!data->perp_wall_dist) // HERE!
		// 	break ;
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr,
		data->mlx_data->mlx_img, 0, 0);
	return (0);
}
