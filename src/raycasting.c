/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/23 07:21:10 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/cub3d.h"

/*
A first few variables are declared: posX and posY represent the position vector of the player, 
dirX and dirY represent the direction of the player, 
and planeX and planeY the camera plane of the player. 
Make sure the camera plane is perpendicular to the direction, but you can change the length of it. 
The ratio between the length of the direction and the camera plane determinates the FOV, here the direction vector is a bit longer than the camera plane, 
so the FOV will be smaller than 90° (more precisely, the FOV is 2 * atan(0.66/1.0)=66°, which is perfect for a first person shooter game). 
Later on when rotating around with the input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length.
*/


// gets the color according to given color scheme
int	get_color(t_cub *data, int mapX, int mapY)
{
	int	color;
	
	//choose wall color
	switch(worldMap[mapX][mapY])
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

//The variables time and oldTime will be used to store the time of the current and the previous frame, the time difference between these two can be used to determinate how much you should move when a certain key is pressed (to move a constant speed no matter how long the calculation of the frames takes), and for the FPS counter.
int	raycasting(t_cub *data)
{
	int	x;
	int	i;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;

	x = 0;
	
	if (data->mlx_data->mlx_img)
	{
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
		data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx_ptr, \
				data->mlx_data->win_width, data->mlx_data->win_height);
	}

	while (x < screenWidth)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		rayDirX = data->dir.x + data->plane.x * cameraX;
		rayDirY = data->dir.y + data->plane.y * cameraX;

		//which box of the map we're in
		mapX = (int)data->pos.x;
		mapY = (int)data->pos.y;		

		//length of ray from one x or y-side to next x or y-side
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		//what direction to step in x or y-direction (either +1 or -1)

		hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				data->side_hit = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				data->side_hit = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (data->side_hit == 0)
			data->perp_wall_dist = (sideDistX - deltaDistX);
		else
			data->perp_wall_dist = (sideDistY - deltaDistY);


		//Calculate height of line to draw on screen
		lineHeight = (int)(screenHeight / data->perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		color = get_color(data, mapX, mapY);
		//draw the pixels of the stripe as a vertical line
		i = 0;
		while (i < drawStart)
			my_mlx_pixel_put(data->mlx_data, x, i++, data->c_col);
		i = drawStart; // not needed?
		while (i < drawEnd)
			my_mlx_pixel_put(data->mlx_data, x, i++, color);
		i = drawEnd;
		while (i < screenHeight)
			my_mlx_pixel_put(data->mlx_data, x, i++, data->f_col);
		x++;
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->mlx_data->mlx_img, 0, 0);
	return (0);
}
