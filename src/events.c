/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:55:27 by raweber           #+#    #+#             */
/*   Updated: 2022/08/31 17:23:32 by ljahn            ###   ########.fr       */
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
	temp = data->perp_dir.x;
	data->perp_dir.x = data->perp_dir.x * cos(direction) \
		- data->perp_dir.y * sin(direction);
	data->perp_dir.y = temp * sin(direction) \
		+ data->perp_dir.y * cos(direction);
	temp = data->plane.x;
	data->plane.x = data->plane.x * cos(direction) - data->plane.y \
		* sin(direction);
	data->plane.y = temp * sin(direction) + data->plane.y * cos(direction);
}

// The deal_key function handles the user input of different keys.
// WSAD move in 4 directions, left&right arrow switch the view left/right
// If ESC is pressed, the whole program stops.
int	deal_key(int key, t_cub *data)
{
	// printf("key is: %d\n", key);
	if (key == Key_ESC)
		destroy(data, NULL);
	if (key == 53)
	{
		destroy(data, NULL);
		return (0);
	}
	// rotate left
	if (key == Key_RIGHT)
	{
		rotating_view(data, -0.05);
		raycasting(data);
	}
	if (key == Key_LEFT)
	{
		rotating_view(data, 0.05);
		raycasting(data);
	}
	if (key == Key_W && data->world_map[(int)(data->pos.x + data->dir.x)] \
		[(int)(data->pos.y + data->dir.y)] == 48)
	{
		data->pos.x += data->dir.x;
		data->pos.y += data->dir.y;
		raycasting(data);
	}
	deal_key_2(key, data);
	return (0);
}

void	deal_key_2(int key, t_cub *data)
{
	if (key == Key_S && data->world_map[(int)(data->pos.x - data->dir.x)] \
		[(int)(data->pos.y - data->dir.y)] == 48)
	{
		data->pos.x -= data->dir.x;
		data->pos.y -= data->dir.y;
		raycasting(data);
	}
	if (key == Key_D && (int)(data->pos.y + data->dir.y) < screenHeight \
		&& (int)(data->pos.y + data->dir.y) > 0 && \
		data->world_map[(int)(data->pos.x + data->perp_dir.x)] \
		[(int)(data->pos.y + data->perp_dir.y)] == 48)
	{
		data->pos.x += data->perp_dir.x;
		data->pos.y += data->perp_dir.y;
		raycasting(data);
	}
	if (key == Key_A && (int)(data->pos.y - data->dir.y) > 0 && \
		data->world_map[(int)(data->pos.x + data->perp_dir.x)] \
		[(int)(data->pos.y - data->perp_dir.y)] == 48)
	{
		data->pos.x -= data->perp_dir.x;
		data->pos.y -= data->perp_dir.y;
		raycasting(data);
	}
}
