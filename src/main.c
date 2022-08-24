/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/08/24 22:01:10 by ljahn            ###   ########.fr       */
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

//  initializes view according to orientation of player
void	set_view_direction(t_cub *data)
{
	if (data->orientation == 'W')
	{
		data->dir.x = 0;
		data->dir.y = -1;
	}
	else if (data->orientation == 'S')
	{
		data->dir.x = 1;
		data->dir.y = 0;
	}
	else if (data->orientation == 'E')
	{
		data->dir.x = 0;
		data->dir.y = 1;
	}
	else if (data->orientation == 'N')
	{
		data->dir.x = -1;
		data->dir.y = 0;
	}
	// else statement needed or is it bulletproof?
}

int	init_data(t_cub *data)
{
	data->pos.x = 3;
	data->pos.y = 7; //x and y start position

	data->orientation = 'S'; // -->> LINUS SETS THIS!
	set_view_direction(data);
	
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->plane.x = data->perp_dir.x;
	data->plane.y = data->perp_dir.y; //the 2d raycaster version of camera plane
	data->perp_wall_dist = 0;
	data->ray_dir.x = 0;
	data->ray_dir.y = 0;
	data->map_check.x = 0;
	data->map_check.y = 0;
	data->side_hit = 0;
	data->f_col = 0x33cc33;
	data->c_col = 0x9999ff;
	
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;

	data->mapX = 0;
	data->mapY = 0;
	data->side_dist.x = 0;
	data->side_dist.y = 0;
	data->delta_dist.x = 0;
	data->delta_dist.y = 0;


	data->mlx_data = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx_data)
		return (1);
	data->mlx_data->mlx_ptr = NULL;
	data->mlx_data->mlx_img = NULL;
	data->mlx_data->win_ptr = NULL;
	data->mlx_data->mlx_img_addr = NULL;
	data->mlx_data->win_width = screenWidth;
	data->mlx_data->win_height = screenHeight;
	data->mlx_data->bits_per_pxl = 0;
	data->mlx_data->line_len = 0;
	data->mlx_data->endian = 0;

	data->n_path = "textures/eagle.xpm";
	data->s_path = "textures/greystone.xpm";
	data->e_path = "textures/mossy.xpm";
	data->w_path = "textures/redbrick.xpm";
	data->n_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->n_wall)
		return (1);
	data->s_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->s_wall)
		return (1);
	data->e_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->e_wall)
		return (1);
	data->w_wall = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!data->w_wall)
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
		return (1); // error message here?
	if (init_data(data))
		return (1); // error message here?
	valid_map(av[1], data);
	// PARSING/READING GOES HERE
	init_mlx(data->mlx_data);
	// GAME LOOP GOES HERE
	raycasting(data);
	
	mlx_hook(data->mlx_data->win_ptr, 2, 0, &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy, data);
	mlx_loop(data->mlx_data->mlx_ptr);
	return (0);
}
