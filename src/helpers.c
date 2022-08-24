/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:05:16 by raweber           #+#    #+#             */
/*   Updated: 2022/08/24 21:47:36 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// gets the color according to given color scheme
int	get_color(t_cub *data, int mapX, int mapY) // REPLACE WITH XPM FILES!
{
	int	color;

	//choose wall color
	switch(data->world_map[mapX][mapY])
	{
		case 1:  color = 0xFF0000;  break; //red
		case 2:  color = 0x00FF00;  break; //green
		case 3:  color = 0x0000FF;   break; //blue
		case 4:  color = 0xFFFFFF;  break; //white
		default: color = 0xFFEA00; break; //yellow
	}
	//give x and y sides different brightness
	if (data->side_hit == 1)
		color = color / 2;
	return (color);
}

int	rgba_to_int(t_color colors)
{
	return (colors.alpha << 24 | colors.red << 16 | colors.green << 8 | colors.blue);
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
}