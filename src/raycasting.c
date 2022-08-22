/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 09:06:52 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480


/*
A first few variables are declared: posX and posY represent the position vector of the player, 
dirX and dirY represent the direction of the player, 
and planeX and planeY the camera plane of the player. 
Make sure the camera plane is perpendicular to the direction, but you can change the length of it. 
The ratio between the length of the direction and the camera plane determinates the FOV, here the direction vector is a bit longer than the camera plane, 
so the FOV will be smaller than 90° (more precisely, the FOV is 2 * atan(0.66/1.0)=66°, which is perfect for a first person shooter game). 
Later on when rotating around with the input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length.
*/
int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//The variables time and oldTime will be used to store the time of the current and the previous frame, the time difference between these two can be used to determinate how much you should move when a certain key is pressed (to move a constant speed no matter how long the calculation of the frames takes), and for the FPS counter.
int	raycasting(t_cub *data)
{
	int	x;

	x = 0;
	if (data->mlx_data->mlx_img)
	{
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
		data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx_ptr, \
				data->mlx_data->win_width, data->mlx_data->win_height);
	}
	// double posX = 7, posY = 20;  //x and y start position
	// double dirX = -1, dirY = 0; //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	//commented out: screen(screenWidth, screenHeight, 0, "Raycaster");

	// while (1)
	// {
		while (x < screenWidth)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
			double rayDirX = data->dir.x + data->plane.x * cameraX;
			double rayDirY = data->dir.y + data->plane.y * cameraX;

			//which box of the map we're in
			int mapX = (int)data->pos.x;
			int mapY = (int)data->pos.y;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;
			int	hit;

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
			int lineHeight = (int)(screenHeight / data->perp_wall_dist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if (drawEnd >= screenHeight)
				drawEnd = screenHeight - 1;
			
			//choose wall color
			int color;
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

			//draw the pixels of the stripe as a vertical line
			while (drawStart < drawEnd)
				my_mlx_pixel_put(data->mlx_data, x, drawStart++, color);
			x++;
			// COMMENTED OUt: verLine(x, drawStart, drawEnd, color);
		}
		mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->mlx_data->mlx_img, 0, 0);
		printf("Finished raycasting iteration\n");

		//timing for input and FPS counter
		// oldTime = time;
		// time = getTicks();
		// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		// printf("%ll", 1.0 / frameTime); //FPS counter
		// redraw();
		// cls();

		//speed modifiers
				// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
				// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

		// readKeys();
		// //move forward if no wall in front of you
		// if (keyDown(SDLK_UP))
		// {
		// 	if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		// 	if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
		// }
		// //move backwards if no wall behind you
		// if (keyDown(SDLK_DOWN))
		// {
		// 	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		// 	if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		// }
		// //rotate to the right
		// if (keyDown(SDLK_RIGHT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// 	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		// }
		// //rotate to the left
		// if (keyDown(SDLK_LEFT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// 	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// 	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		// }
  	// }
	return (0);
}
