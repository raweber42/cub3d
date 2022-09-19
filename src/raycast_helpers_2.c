/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:07:13 by raweber           #+#    #+#             */
/*   Updated: 2022/09/19 11:49:19 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// calculates the x start and end values needed for drawing
void	calculate_draw_range(t_cub *data, int *draw_start, int *draw_end)
{
	data->line_height = (int)(SCREENHEIGHT / data->perp_wall_dist);
	if (data->perp_wall_dist == 0)
		data->line_height = (double) SCREENHEIGHT;
	*draw_start = -data->line_height / 2 + SCREENHEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = data->line_height / 2 + SCREENHEIGHT / 2;
	if (*draw_end >= SCREENHEIGHT)
		*draw_end = SCREENHEIGHT - 1;
}

// helper to colorize floor and ceiling
void	draw_floor_and_ceiling(t_cub *data, int x)
{
	while (data->draw_start >= 0)
		my_mlx_pixel_put(data->mlx_data, x, data->draw_start--, data->c_col);
	while (data->draw_end < SCREENHEIGHT)
		my_mlx_pixel_put(data->mlx_data, x, data->draw_end++, data->f_col);
}

// colorizes all pixels of the current mlx_image.
void	put_all_pixels(t_cub *data, int tex_x, int x)
{
	double	tex_pos;
	int		color;
	double	step;
	int		y;

	calculate_draw_range(data, &data->draw_start, &data->draw_end);
	y = data->draw_start;
	step = (double) TEXHEIGHT / (double) data->line_height;
	tex_pos = (data->draw_start - SCREENHEIGHT / 2 + \
		data->line_height / 2) * step;
	while (y < data->draw_end)
	{
		if (data->side_hit == 0 && data->ray_dir.x > 0)
			color = rgba_to_int(*(data->s_wall->matrix[(int)tex_pos][tex_x]));
		else if (data->side_hit == 0 && data->ray_dir.x < 0)
			color = rgba_to_int(*(data->n_wall->matrix[(int)tex_pos][tex_x]));
		else if (data->side_hit == 1 && data->ray_dir.y < 0)
			color = rgba_to_int(*(data->w_wall->matrix[(int)tex_pos][tex_x]));
		else if (data->side_hit == 1 && data->ray_dir.y > 0)
			color = rgba_to_int(*(data->e_wall->matrix[(int)tex_pos][tex_x]));
		my_mlx_pixel_put(data->mlx_data, x, y++, color);
		tex_pos += step;
	}
	draw_floor_and_ceiling(data, x);
}
