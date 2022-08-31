/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:23:20 by raweber           #+#    #+#             */
/*   Updated: 2022/08/31 07:25:00 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// gets and safes the image address of all wall texture images
void	get_tex_img_address(t_cub *data)
{
	data->n_wall->mlx_img_addr = mlx_get_data_addr(data->n_wall->mlx_img, \
			&data->n_wall->bits_per_pxl, &data->n_wall->line_len, \
			&data->n_wall->endian);
	data->s_wall->mlx_img_addr = mlx_get_data_addr(data->s_wall->mlx_img, \
			&data->s_wall->bits_per_pxl, &data->s_wall->line_len, \
			&data->s_wall->endian);
	data->e_wall->mlx_img_addr = mlx_get_data_addr(data->e_wall->mlx_img, \
			&data->e_wall->bits_per_pxl, &data->e_wall->line_len, \
			&data->e_wall->endian);
	data->w_wall->mlx_img_addr = mlx_get_data_addr(data->w_wall->mlx_img, \
			&data->w_wall->bits_per_pxl, &data->w_wall->line_len, \
			&data->w_wall->endian);
	if (!data->n_wall->mlx_img_addr || !data->s_wall->mlx_img_addr || \
		!data->e_wall->mlx_img_addr || !data->w_wall->mlx_img_addr)
		destroy(data, "Error: Could not get wall image address");
}

// converts all given xpm files to mlx images
void	load_xpm_files(t_cub *data)
{
	int	width;
	int	height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	data->n_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, \
		data->n_path, &height, &width);
	data->s_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, \
		data->s_path, &height, &width);
	data->e_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, \
		data->e_path, &height, &width);
	data->w_wall->mlx_img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, \
		data->w_path, &height, &width);
	if (!data->n_wall->mlx_img || !data->s_wall->mlx_img || \
		!data->e_wall->mlx_img || !data->w_wall->mlx_img)
		destroy(data, "Error: Could not convert xpm file to image");
	get_tex_img_address(data);
}

// sets the color of the given pixel at position (x/y)
t_color	*set_color(t_texture *tex, int y, int x)
{
	int	*pos;

	pos = (int *)tex->mlx_img_addr + (y * tex->line_len / 4 + x * \
		(tex->bits_per_pxl / 32));
	return ((t_color *)pos);
}

// allocates and fills the color matrix for a given texture
t_color	***init_color_matrix(t_texture *x_wall)
{
	int	i;
	int	j;

	x_wall->matrix = ft_calloc(TEXHEIGHT, sizeof(t_color **));
	if (!x_wall->matrix)
		return (NULL);
	i = 0;
	while (i < TEXHEIGHT)
	{
		x_wall->matrix[i] = ft_calloc(TEXWIDTH, sizeof(t_color *));
		j = 0;
		while (j < TEXWIDTH)
		{
			x_wall->matrix[i][j] = set_color(x_wall, i, j);
			j++;
		}
		i++;
	}
	return (x_wall->matrix);
}

// handler for textures that calls subfunctions
void	handle_textures(t_cub *data)
{
	load_xpm_files(data);
	data->n_wall->matrix = init_color_matrix(data->n_wall);
	data->s_wall->matrix = init_color_matrix(data->s_wall);
	data->e_wall->matrix = init_color_matrix(data->e_wall);
	data->w_wall->matrix = init_color_matrix(data->w_wall);
}
