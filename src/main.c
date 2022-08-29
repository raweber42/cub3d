/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/29 17:30:13 by ljahn            ###   ########.fr       */
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
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
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
	printf("Position: %f, %f\n", data->pos.x, data->pos.y);

	set_view_direction(data);
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->plane.x = data->perp_dir.x;
	data->plane.y = data->perp_dir.y;
	data->perp_wall_dist = 0;
	data->ray_dir.x = 0;
	data->ray_dir.y = 0;
	data->side_hit = 0;
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
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
	printf("PATH: |%s|\n", data->n_path);
	printf("PATH: |%s|\n", data->s_path);
	printf("PATH: |%s|\n", data->w_path);
	printf("PATH: |%s|\n", data->e_path);
	// data->n_path = "textures/eagle.xpm";//SET THIS
	// data->s_path = "textures/greystone.xpm";
	// data->e_path = "textures/mossy.xpm";
	// data->w_path = "textures/redbrick.xpm";
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
	
	// if (ac == 2)
	// 	valid_map(av[1]);
	// else
	// 	error_msg("Invalid number of arguments");
	// LINUS########################

	t_cub	*data;

	data = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!data)
	{
		ft_printf("Error: Could not allocate cub3d struct");
		return (1);
	} // error message here?
	valid_map(av[1], data);
	
	if (init_data(data))
		return (1); // error message here?
	// PARSING/READING GOES HERE
	raycasting(data);
	mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy_no_msg, data);
	mlx_loop(data->mlx_data->mlx_ptr);
	return (0);
}
