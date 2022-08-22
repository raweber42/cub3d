/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:20:10 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 11:00:48 by ljahn            ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_cub {
	// old fdf struct
	// char	*argv;
	// void	*mlx_ptr;
	// void	*win_ptr;
	// void	*mlx_img;
	// int		win_width;
	// int		win_height;
	// float	zoom;
	// float	height_zoom;
	// int		default_color;
	// float	angle;
	// int		bits_per_pxl;
	// int		line_len;
	// int		endian;
	// char	*mlx_img_addr;
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

// validation.c
void	error_msg(char *msg);
void	valid_map(char *path);


#endif