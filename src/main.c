/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/25 16:19:06 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->plane.x = data->perp_dir.x;
	data->plane.y = data->perp_dir.y;
	data->perp_wall_dist = 0;
	data->ray_dir.x = 0;
	data->ray_dir.y = 0;
	data->map_check.x = 0;
	data->map_check.y = 0;
	data->side_hit = 0;
	data->f_col = 0x413030;
	data->c_col = 0x000066;
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->mapX = 0;
	data->mapY = 0;
	data->side_dist.x = 0;
	data->side_dist.y = 0;
	data->delta_dist.x = 0;
	data->delta_dist.y = 0;
}

// initializes main struct, player position, view, ray data and textures
int	init_data(t_cub *data)
{
	data->pos.x = 3;
	data->pos.y = 7; // -->> LINUS SETS THIS!
	data->orientation = 'S'; // -->> LINUS SETS THIS!
	set_view_direction(data);
	init_ray_data(data);
	data->mlx_data = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx_data)
		return (1);
	init_mlx(data->mlx_data);
	data->n_path = "textures/eagle.xpm";
	data->s_path = "textures/greystone.xpm";
	data->e_path = "textures/mossy.xpm";
	data->w_path = "textures/redbrick.xpm";
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
	mlx->win_width = screenWidth;
	mlx->win_height = screenHeight;
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
	// LINUS########################
	(void)ac;
	(void)av;
	// valid_map(av[1]);
	
	// if (ac == 2)
	// 	valid_map(av[1]);
	// else
	// 	error_msg("Invalid number of arguments");
	// LINUS########################

	t_cub	*data;

	data = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!data || init_data(data))
		return (1); // error message here?
	// PARSING/READING GOES HERE
	raycasting(data);
	mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy, data);
	mlx_loop(data->mlx_data->mlx_ptr);
	return (0);
}
