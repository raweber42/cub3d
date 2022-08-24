/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:46:25 by raweber           #+#    #+#             */
/*   Updated: 2022/08/24 16:49:54 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx_data, int x, int y, int color)
{
	char	*dst;

	if (x < mlx_data->win_width && y < mlx_data->win_height && x > 0 && y > 0)
	{
		dst = mlx_data->mlx_img_addr + (y * mlx_data->line_len \
								+ x * (mlx_data->bits_per_pxl / 8));
		*(unsigned int *) dst = color;
	} // can the if clause be removed?
}

void	my_mlx_pixel_put_2(t_texture *x_wall, int x, int y, int color)
{
	char	*dst;

	if (x < screenWidth && y < screenHeight && x > 0 && y > 0)
	{
		dst = x_wall->mlx_img_addr + (y * x_wall->line_len \
								+ x * (x_wall->bits_per_pxl / 8));
		*(unsigned int *) dst = color;
	} // can the if clause be removed?
}
