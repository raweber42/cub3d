/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:26:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/24 15:45:37 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/cub3d.h"


void	get_tex_img_address(t_cub *data)
{
	data->n_wall->mlx_img_addr = mlx_get_data_addr(data->n_wall->mlx_img, &data->n_wall->bits_per_pxl, &data->n_wall->line_len, &data->n_wall->endian);
	data->s_wall->mlx_img_addr = mlx_get_data_addr(data->s_wall->mlx_img, &data->s_wall->bits_per_pxl, &data->s_wall->line_len, &data->s_wall->endian);
	data->e_wall->mlx_img_addr = mlx_get_data_addr(data->e_wall->mlx_img, &data->e_wall->bits_per_pxl, &data->e_wall->line_len, &data->e_wall->endian);
	data->w_wall->mlx_img_addr = mlx_get_data_addr(data->w_wall->mlx_img, &data->w_wall->bits_per_pxl, &data->w_wall->line_len, &data->w_wall->endian);
	// error checking (=NULL) needed here?
}

void	load_xpm_files(t_cub *data)
{
	int	width;
	int height;

	width = TEXWIDTH; // needed?
	height = TEXHEIGHT; // needed?
	data->n_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, data->n_path, &height, &width);
	data->s_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, data->s_path, &height, &width);
	data->e_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, data->e_path, &height, &width);
	data->w_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, data->w_path, &height, &width);
	if (!data->n_wall->mlx_img || !data->s_wall->mlx_img || !data->e_wall->mlx_img || !data->w_wall->mlx_img)
		destroy(data); // check if this is the right procedure at this moment!
	get_tex_img_address(data);
}

// int	set_color(t_texture *x_wall, int y, int x)
// {
// 	int	color;

// 	color = *(x_wall->mlx_img_addr + (y * x_wall->line_len + x * (x_wall->bits_per_pxl / 8)));
// 	printf("value of endian is: %d\n", x_wall->endian);
// 	return (color); // too simple?
// }

// JORIT VERSION
static t_color	*set_color(t_texture *tex, int x, int y)
{
	int	*pos;

	pos = (int *)tex->mlx_img_addr + (y * tex->line_len + x * (tex->bits_per_pxl / 8));
	// printf("size_line is: %d\n", tex->line_len);
	return ((t_color *)pos);
}
// JORIT VERSION

t_color	***init_color_matrix(t_texture *x_wall) // could be void type too
{
	int	i;
	int	j;

	x_wall->matrix = ft_calloc(TEXHEIGHT, sizeof(int **));
	if (!x_wall->matrix)
		return (NULL);
	i = 0;
	while (i < TEXHEIGHT)
	{
		x_wall->matrix[i] = ft_calloc(TEXWIDTH, sizeof(int *));
		j = 0;
		while (j < TEXWIDTH)
		{
			x_wall->matrix[i][j] = set_color(x_wall, i, j);
			j++;
		}
		i++;
	}
	// jorit sets height here
	return (x_wall->matrix);
}

void	handle_textures(t_cub *data)
{
	load_xpm_files(data);
	data->n_wall->matrix = init_color_matrix(data->n_wall);
	data->s_wall->matrix = init_color_matrix(data->s_wall);
	data->e_wall->matrix = init_color_matrix(data->e_wall);
	data->w_wall->matrix = init_color_matrix(data->w_wall);
}

// calculates height of line to draw on screen, colorizes it accordingly
// and fills bottom and top with floor- and ceiling-color
void	draw_pixels(t_cub *data, int x)
{
	int	i;
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(screenHeight / data->perp_wall_dist);
	draw_start = -line_height / 2 + screenHeight / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + screenHeight / 2;
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	
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
	double	step = 1.0 * TEXHEIGHT / line_height;
	double	texPos = (draw_start - mapHeight / 2 + line_height / 2) * step;  // is mapheight right?
	for (int y = draw_start; y < draw_end; y++)
	{
		int texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		// uint32_t	color =  data->n_wall->mlx_img_addr[TEXHEIGHT * texY + texX];
		// buffer[y][x] = color;
		// printf("current color: %d\n", rgba_to_int(*(data->n_wall->matrix[texY][texX])));
		my_mlx_pixel_put(data->mlx_data, x, y, rgba_to_int(*(data->n_wall->matrix[texY][texX])));
	}


		
	// color = get_color(data, data->mapX, data->mapY); // only for untextured



	i = 0;
	while (i < draw_start)
		my_mlx_pixel_put(data->mlx_data, x, i++, data->c_col);
	// while (i < draw_end)
	// 	my_mlx_pixel_put(data->mlx_data, x, i++, color);
	i = draw_end;
	while (i < screenHeight)
		my_mlx_pixel_put(data->mlx_data, x, i++, data->f_col);
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
		if (worldMap[data->mapX][data->mapY] == 1) // walls always '1'?
			hit = 1;
	}
}

// temp old from monday
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
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr,
		data->mlx_data->mlx_img, 0, 0);
	return (0);
}
