/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:20:10 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 09:19:10 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#if defined(__linux__)
    # include "../minilibx_linux/mlx.h"
#else
    # include "../minilibx_macos/mlx.h"
#endif
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

enum
{
	Key_A = 0,
	Key_S = 1,
	Key_D = 2,
	Key_W = 13,
	Key_ESC = 53,
	Key_LEFT = 123,
	Key_RIGHT = 124,
	Key_DOWN = 125,
	Key_UP = 126
};

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_cub {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	camera;
	t_vector	ray_dir;
	t_vector	perp_dir;
	
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		side_hit; //was a NS or a EW wall hit?
	

	
	int		x_offset;
	int		y_offset;
	int		height;
	int		width;


	int		iso_x;
	int		iso_y;
	int		iso_x1;
	int		iso_y1;
	struct s_mlx	*mlx_data;
	// end old fdf struct
}				t_cub;

typedef struct s_mlx {
	// old fdf struct
	char	*argv;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_img;
	int		win_width;
	int		win_height;
	float	zoom;
	float	height_zoom;
	int		default_color;
	float	angle;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
	char	*mlx_img_addr;
}				t_mlx;



// main.c
void	init_data(t_cub *data);
void	init_mlx(t_mlx *mlx_data);


// my_put_pixel.c
void	my_mlx_pixel_put(t_mlx *mlx_data, int x, int y, int color);

// events.c
int	deal_key(int key, t_cub *data);

// destroy.c
int	destroy(t_cub *data);

// raycasting.c
int	raycasting(t_cub *data);


#endif