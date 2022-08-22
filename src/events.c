/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:55:27 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 09:28:57 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//both camera direction and camera plane must be rotated
void	rotating_view(t_cub *data, float direction)
{
	double	temp;

	temp = data->dir.x;
	data->dir.x = data->dir.x * cos(direction) - data->dir.y * sin(direction);
	data->dir.y = temp * sin(direction) + data->dir.y * cos(direction);
	// temp = data->perp_dir.x;
	// data->perp_dir.x = data->perp_dir.x * cos(-0.05) - data->perp_dir.y * sin(-0.05);
	// data->perp_dir.y = temp * sin(-0.05) + data->perp_dir.y * cos(-0.05);
	temp = data->plane.x;
	data->plane.x = data->plane.x * cos(direction) - data->plane.y * sin(direction);
	data->plane.y = temp * sin(direction) + data->plane.y * cos(direction);
}

// The deal_key function handles the user input of different keys.
// If ESC is pressed, the whole program stops.
int	deal_key(int key, t_cub *data)
{
	// put key combinations here!
	printf("key is: %d\n", key);
	if (key == 53)
	{
		destroy(data);
		return (0);
	}
	// rotate left
	if (key == Key_LEFT)
	{
		rotating_view(data, -0.05);
		raycasting(data);
	}
	// rotate right
	if (key == Key_RIGHT)
	{
		rotating_view(data, 0.05);
		raycasting(data);
	}
	if (key == Key_W)
	{
		data->pos.x += data->dir.x;
		raycasting(data);
	}
	if (key == Key_S)
	{
		data->pos.x -= data->dir.x;
		raycasting(data);
	}
	if (key == Key_A)
	{
		data->pos.y += data->dir.y;
		raycasting(data);
	}
	if (key == Key_D)
	{
		data->pos.y -= data->dir.y;
		raycasting(data);
	}
	

	// raycasting(data);
	return (0);
}