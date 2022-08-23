/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/23 11:31:55 by raweber          ###   ########.fr       */
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

// //The variables time and oldTime will be used to store the time of the current and the previous frame, the time difference between these two can be used to determinate how much you should move when a certain key is pressed (to move a constant speed no matter how long the calculation of the frames takes), and for the FPS counter.
// int	raycasting(t_cub *data)
// {
// 	int	x;
// 	int	i;
// 	// double	cameraX;
// 	// double	ray_dir.x;
// 	// double	ray_dir.y;
// 	// int		mapX;
// 	// int		mapY;
// 	// double	side_dist.x;
// 	// double	side_dist.y;
// 	// double	delta_dist.x;
// 	// double	delta_dist.y;
// 	// data->ray_dir.x = 0;
// 	// data->ray_dir.y = 0;
// 	// data->mapX = 0;
// 	// data->mapY = 0;
// 	// data->side_dist.x = 0;
// 	// data->side_dist.y = 0;
// 	// data->delta_dist.x = 0;
// 	// data->delta_dist.y = 0;
// 	int		stepX;
// 	int		stepY;
// 	int		hit;
// 	int		lineHeight;
// 	int		drawStart;
// 	int		drawEnd;
// 	int		color;

// 	x = 0;
	
// 	if (data->mlx_data->mlx_img)
// 	{
// 		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
// 		data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx_ptr, \
// 				data->mlx_data->win_width, data->mlx_data->win_height);
// 	}

// 	while (x < screenWidth)
// 	{
// 		//calculate ray position and direction
// 		data->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
// 		data->ray_dir.x = data->dir.x + data->plane.x * data->cameraX;
// 		data->ray_dir.y = data->dir.y + data->plane.y * data->cameraX;

// 		//which box of the map we're in
// 		data->mapX = (int)data->pos.x;
// 		data->mapY = (int)data->pos.y;		

// 		//length of ray from one x or y-side to next x or y-side
// 		data->delta_dist.x = (data->ray_dir.x == 0) ? 1e30 : fabs(1 / data->ray_dir.x);
// 		data->delta_dist.y = (data->ray_dir.y == 0) ? 1e30 : fabs(1 / data->ray_dir.y);
// 		//what direction to step in x or y-direction (either +1 or -1)

// 		hit = 0; //was there a wall hit?

// 		//calculate step and initial sideDist
// 		if (data->ray_dir.x < 0)
// 		{
// 			stepX = -1;
// 			data->side_dist.x = (data->pos.x - data->mapX) * data->delta_dist.x;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			data->side_dist.x = (data->mapX + 1.0 - data->pos.x) * data->delta_dist.x;
// 		}
// 		if (data->ray_dir.y < 0)
// 		{
// 			stepY = -1;
// 			data->side_dist.y = (data->pos.y - data->mapY) * data->delta_dist.y;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			data->side_dist.y = (data->mapY + 1.0 - data->pos.y) * data->delta_dist.y;
// 		}
// 		//perform DDA
// 		while (hit == 0)
// 		{
// 			//jump to next map square, either in x-direction, or in y-direction
// 			if (data->side_dist.x < data->side_dist.y)
// 			{
// 				data->side_dist.x += data->delta_dist.x;
// 				data->mapX += stepX;
// 				data->side_hit = 0;
// 			}
// 			else
// 			{
// 				data->side_dist.y += data->delta_dist.y;
// 				data->mapY += stepY;
// 				data->side_hit = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (worldMap[data->mapX][data->mapY] > 0)
// 				hit = 1;
// 		}
// 		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
// 		if (data->side_hit == 0)
// 			data->perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
// 		else
// 			data->perp_wall_dist = (data->side_dist.y - data->delta_dist.y);


// 		//Calculate height of line to draw on screen
// 		lineHeight = (int)(screenHeight / data->perp_wall_dist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		drawStart = -lineHeight / 2 + screenHeight / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + screenHeight / 2;
// 		if (drawEnd >= screenHeight)
// 			drawEnd = screenHeight - 1;
// 		color = get_color(data, data->mapX, data->mapY);
// 		//draw the pixels of the stripe as a vertical line
// 		i = 0;
// 		while (i < drawStart)
// 			my_mlx_pixel_put(data->mlx_data, x, i++, data->c_col);
// 		i = drawStart; // not needed?
// 		while (i < drawEnd)
// 			my_mlx_pixel_put(data->mlx_data, x, i++, color);
// 		i = drawEnd;
// 		while (i < screenHeight)
// 			my_mlx_pixel_put(data->mlx_data, x, i++, data->f_col);
// 		x++;
// 	}
// 	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->mlx_data->mlx_img, 0, 0);
// 	return (0);
// }

void	mlx_image_check(t_cub *data)
{
	if (data->mlx_data->mlx_img)
	{
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
		data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx_ptr, \
				data->mlx_data->win_width, data->mlx_data->win_height);
	}
}

void	draw_pixels(t_cub *data, int x)
{
	int	i;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	//Calculate height of line to draw on screen
	line_height = (int)(screenHeight / data->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + screenHeight / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + screenHeight / 2;
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	color = get_color(data, data->mapX, data->mapY);
	i = 0;
	while (i < draw_start)
		my_mlx_pixel_put(data->mlx_data, x, i++, data->c_col);
	while (i < draw_end)
		my_mlx_pixel_put(data->mlx_data, x, i++, color);
	while (i < screenHeight)
		my_mlx_pixel_put(data->mlx_data, x, i++, data->f_col);
}

void	handle_rays_and_dda(t_cub *data, int x)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	// double	sideDistX;
	// double	sideDistY;
	// double	deltaDistX;
	// double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	
	//calculate ray position and direction
	cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
	rayDirX = data->dir.x + data->plane.x * cameraX;
	rayDirY = data->dir.y + data->plane.y * cameraX;

	//which box of the map we're in
	data->mapX = (int)data->pos.x;
	data->mapY = (int)data->pos.y;		

	//length of ray from one x or y-side to next x or y-side
	data->delta_dist.x = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	data->delta_dist.y = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	//what direction to step in x or y-direction (either +1 or -1)

	
	//calculate step and initial sideDist
	if (rayDirX < 0)
	{
		stepX = -1;
		data->side_dist.x = (data->pos.x - data->mapX) * data->delta_dist.x;
	}
	else
	{
		stepX = 1;
		data->side_dist.x = (data->mapX + 1.0 - data->pos.x) * data->delta_dist.x;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		data->side_dist.y = (data->pos.y - data->mapY) * data->delta_dist.y;
	}
	else
	{
		stepY = 1;
		data->side_dist.y = (data->mapY + 1.0 - data->pos.y) * data->delta_dist.y;
	}
	//perform DDA
	hit = 0; //was there a wall hit?
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_dist.x;
			data->mapX += stepX;
			data->side_hit = 0;
		}
		else
		{
			data->side_dist.y += data->delta_dist.y;
			data->mapY += stepY;
			data->side_hit = 1;
		}
		//Check if ray has hit a wall
		if (worldMap[data->mapX][data->mapY] == 1) // change, if walls can also be different from '1'!
			hit = 1;
	}
}

// temp old from monday
int	raycasting(t_cub *data)
{
	int	x;

	x = 0;
	mlx_image_check(data);
	while (x < screenWidth)
	{
		handle_rays_and_dda(data, x);
		
		
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (data->side_hit == 0)
			data->perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
		else
			data->perp_wall_dist = (data->side_dist.y - data->delta_dist.y);

		draw_pixels(data, x++);
		
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->mlx_data->mlx_img, 0, 0);
	return (0);
}