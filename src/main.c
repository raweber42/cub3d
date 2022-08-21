/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/21 17:18:39 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_cub *data)
{
	data->mlx_data = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	// error checking here!
	data->mlx_data->mlx_ptr = NULL;
	data->mlx_data->mlx_img = NULL;
	data->mlx_data->win_ptr = NULL;
	data->mlx_data->mlx_img_addr = NULL;
	data->mlx_data->win_width = 1000;
	data->mlx_data->win_height = 1000;
	data->mlx_data->angle = 0.9;
	data->mlx_data->bits_per_pxl = 0;
	data->mlx_data->line_len = 0;
	data->mlx_data->endian = 0;
}

void	init_mlx(t_mlx *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, \
					mlx_data->win_width, mlx_data->win_height, "Cub3d");
	mlx_data->mlx_img = mlx_new_image(mlx_data->mlx_ptr, \
					mlx_data->win_width, mlx_data->win_height);
	mlx_data->mlx_img_addr = mlx_get_data_addr(mlx_data->mlx_img, \
					&mlx_data->bits_per_pxl, &mlx_data->line_len, &mlx_data->endian);
}

int	main(void)
{
	t_cub	*data;
	
	data = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!data)
		return (0);
	// error checking goes here!
	init_data(data);
	// PARSING/READING GOES HERE
	init_mlx(data->mlx_data);
	// GAME LOOP GOES HERE

	raycasting(data);
	// HEEEEEERREEEEEEE DESTROYING ON SUNDAY
	
	mlx_hook(data->mlx_data->win_ptr, 2, 0, &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy, data);
	mlx_loop(data->mlx_data->mlx_ptr);
}