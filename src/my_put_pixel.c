/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:46:25 by raweber           #+#    #+#             */
/*   Updated: 2022/08/25 10:14:00 by raweber          ###   ########.fr       */
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
	}
}
