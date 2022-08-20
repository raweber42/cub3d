/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:20:10 by raweber           #+#    #+#             */
/*   Updated: 2022/08/20 17:45:04 by raweber          ###   ########.fr       */
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
	int		**z_matrix;
	int		**color_matrix;

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

#endif