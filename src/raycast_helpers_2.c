/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:07:13 by raweber           #+#    #+#             */
/*   Updated: 2022/08/26 12:11:52 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_draw_range(t_cub *data, int *draw_start, int *draw_end)
{
	data->line_height = (int)(screenHeight / data->perp_wall_dist);
	if (data->perp_wall_dist == 0)
		data->line_height = (double) screenHeight;
	*draw_start = -data->line_height / 2 + screenHeight / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = data->line_height / 2 + screenHeight / 2;
	if (*draw_end >= screenHeight)
		*draw_end = screenHeight - 1;
}

void	draw_floor_and_ceiling(t_cub *data, int x)
{
	while (data->draw_start >= 0)
		my_mlx_pixel_put(data->mlx_data, x, data->draw_start--, data->c_col);
	while (data->draw_end < screenHeight)
		my_mlx_pixel_put(data->mlx_data, x, data->draw_end++, data->f_col);
}

void	put_all_pixels(t_cub *data, int tex_x, int x)
{
	double	tex_pos;
	int		tex_y;
	int		color;
	double	step;
	int		y;

	calculate_draw_range(data, &data->draw_start, &data->draw_end);
	y = data->draw_start;
	step = (double) TEXHEIGHT / (double) data->line_height;
	tex_pos = (data->draw_start - screenHeight / 2 + \
		data->line_height / 2) * step;
	while (y < data->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		if (data->side_hit == 0 && data->ray_dir.x > 0)
			color = rgba_to_int(*(data->s_wall->matrix[tex_y][tex_x]));
		else if (data->side_hit == 0 && data->ray_dir.x < 0)
			color = rgba_to_int(*(data->n_wall->matrix[tex_y][tex_x]));
		else if (data->side_hit == 1 && data->ray_dir.y < 0)
			color = rgba_to_int(*(data->w_wall->matrix[tex_y][tex_x]));
		else if (data->side_hit == 1 && data->ray_dir.y > 0)
			color = rgba_to_int(*(data->e_wall->matrix[tex_y][tex_x]));
		my_mlx_pixel_put(data->mlx_data, x, y++, color);
	}
	draw_floor_and_ceiling(data, x);
}
