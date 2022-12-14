/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/10/21 17:45:32 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// initializes the wall structs and sets all variables to zero
int	init_walls(t_cub *data)
{
	if (allocate_walls(data))
		return (1);
	data->n_wall->mlx_img = NULL;
	data->n_wall->mlx_img_addr = NULL;
	data->n_wall->bits_per_pxl = 0;
	data->n_wall->line_len = 0;
	data->n_wall->endian = 0;
	data->s_wall->mlx_img = NULL;
	data->s_wall->mlx_img_addr = NULL;
	data->s_wall->bits_per_pxl = 0;
	data->s_wall->line_len = 0;
	data->s_wall->endian = 0;
	data->e_wall->mlx_img = NULL;
	data->e_wall->mlx_img_addr = NULL;
	data->e_wall->bits_per_pxl = 0;
	data->e_wall->line_len = 0;
	data->e_wall->endian = 0;
	data->w_wall->mlx_img = NULL;
	data->w_wall->mlx_img_addr = NULL;
	data->w_wall->bits_per_pxl = 0;
	data->w_wall->line_len = 0;
	data->w_wall->endian = 0;
	return (0);
}

// initializes all ray data and sets floor/ceiling color
void	init_ray_data(t_cub *data)
{
	set_view_direction(data);
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->perp_wall_dist = 0;
	data->ray_dir.x = 0;
	data->ray_dir.y = 0;
	data->side_hit = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->side_dist.x = 0;
	data->side_dist.y = 0;
	data->delta_dist.x = 0;
	data->delta_dist.y = 0;
}

// initializes main struct, player position, view, ray data and textures
int	init_data(t_cub *data)
{
	set_view_direction(data);
	init_ray_data(data);
	data->mlx_data = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx_data)
		return (1);
	init_mlx(data->mlx_data);
	init_walls(data);
	return (0);
}

// initializes the required mlx data
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_img = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_img_addr = NULL;
	mlx->win_width = SCREENWIDTH;
	mlx->win_height = SCREENHEIGHT;
	mlx->bits_per_pxl = 0;
	mlx->line_len = 0;
	mlx->endian = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
					mlx->win_width, mlx->win_height, "Cub3d");
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, \
					mlx->win_width, mlx->win_height);
	mlx->mlx_img_addr = mlx_get_data_addr(mlx->mlx_img, \
					&mlx->bits_per_pxl, &mlx->line_len, &mlx->endian);
}

/*
starts and runs the whole cub3d application
for mac: mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
for linux: mlx_key_hook(data->mlx_data->win_ptr, &deal_key, data);
*/
int	main(int ac, char **av)
{
	t_cub	*data;

	if (ac != 2)
		error_msg("Invalid number of arguments", NULL);
	data = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!data)
		error_msg("Could not allocate cub3d struct", NULL);
	ft_lstadd_back(&data->free_list, ft_lstnew(data));
	parsing(data, av);
	if (init_data(data))
		return (1);
	raycasting(data);
	mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy_no_msg, data);
	mlx_loop(data->mlx_data->mlx_ptr);
	return (0);
}
