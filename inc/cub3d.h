/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:20:10 by raweber           #+#    #+#             */
/*   Updated: 2022/08/31 19:36:49 by ljahn            ###   ########.fr       */
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


# define mapWidth 24
# define mapHeight 24
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define screenWidth 1000
# define screenHeight 1000

#if defined(__linux__)
	enum
	{
		Key_A = 97,
		Key_S = 115,
		Key_D = 100,
		Key_W = 119,
		Key_ESC = 65307,
		Key_LEFT = 65361,
		Key_RIGHT = 65363,
		Key_DOWN = 125,
		Key_UP = 126
	};
#else
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
#endif


enum
{
	FORWARD,
	BACK,
	RIGHT,
	LEFT
};

// delete
extern int worldMap[24][24];
// delete!

typedef int	(*rec_fun)(char **, int, int);

typedef struct s_mlx {
	char	*argv;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_img;
	int		win_width;
	int		win_height;

	int		bits_per_pxl;
	int		line_len;
	int		endian;
	char	*mlx_img_addr;
}				t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_color
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	alpha;
}	t_color;

typedef struct s_texture
{
	void	*mlx_img;
	char	*mlx_img_addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
	t_color	***matrix;
}		t_texture;

typedef struct s_cub {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_dir;
	t_vector	perp_dir;
	int			map_x;
	int			map_y;
	t_vector	map_check;
	// HERE
	int			mapX;
	int			mapY;
	t_vector	side_dist;
	t_vector	delta_dist;
	int			line_height;
	char		orientation;
	double		perp_wall_dist;
	int			side_hit;
	int			f_col;
	int			c_col;
	int			draw_start;
	int			draw_end;
	t_mlx		*mlx_data;
	char		*n_path;
	char		*s_path;
	char		*e_path;
	char		*w_path;
	t_texture	*n_wall;
	t_texture	*s_wall;
	t_texture	*e_wall;
	t_texture	*w_wall;
	char		**world_map;
}				t_cub;

typedef struct s_attr
{
	int		fd;
	char	*line;
	char	**splitters;
	char	**splitters2;
	int		counter;
	int		i;
}	t_attr;

typedef struct s_closed
{
	int	i;
	int	j;
	int	player;
	int	limit;
	int	ulimit;
}	t_closed;

typedef struct s_gelem
{
	int	fd;
	int	i;
	char *line;
	int	max_l;
}	t_gelem;

typedef struct s_fm
{
	int	fd;
	int	i;
	int	j;
	char	*line;
}	t_fm;

// main.c
void	set_view_direction(t_cub *data);
int		init_data(t_cub *data);
void	init_mlx(t_mlx *mlx_data);

// my_put_pixel.c
void	my_mlx_pixel_put(t_mlx *mlx_data, int x, int y, int color);

// events.c
int		deal_key(int key, t_cub *data);
void	deal_key_2(int key, t_cub *data);

// destroy.c
int		destroy(t_cub *data, char *str);
int		destroy_no_msg(t_cub *data);

void	destroy_wall(t_texture *wall);

// raycasting.c
int		raycasting(t_cub *data);

// raycast_helpers.c
void	get_tex_img_address(t_cub *data);
void	load_xpm_files(t_cub *data);
t_color	*set_color(t_texture *tex, int y, int x);
t_color	***init_color_matrix(t_texture *x_wall);
void	handle_textures(t_cub *data);

// raycast_helpers_2.c
void	calculate_draw_range(t_cub *data, int *draw_start, int *draw_end);
void	put_all_pixels(t_cub *data, int tex_x, int x);

// helpers.c
int		allocate_walls(t_cub *data);
void	set_view_direction(t_cub *data);
int		rgba_to_int(t_color colors);
void	mlx_image_reload(t_cub *data);

// validation.c
void	error_msg(char *msg);
void	valid_map(char *path, t_cub *data);
int		surounded(char **matrix, int i, int j, int callback);

// matrix.c
char	**get_matrix(char *path, int lines);
int		elem_cnt(char *path);
void	free_all(char **splitters);

// linus_utils.c
void	free_all(char **splitters);
char	*leaktrim(char *s1, char *set);
int		ft_strstrlen(char **strstr);
void	free_all(char **splitters);
void	error_msg(char *msg);

// recursive_madness.c
int		left_border(char **matrix, int i, int j);
int		right_border(char **matrix, int i, int j);
int		left_one(char **matrix, int i, int j);
int		right_one(char **matrix, int i, int j);
int		allowed_char(char c);

// recursive_madness2.c
int		closed_left(char **matrix, int i, int j);
int		closed_up(char **matrix, int i, int j);
int		closed_right(char **matrix, int i, int j);
int		closed_down(char **matrix, int i, int j);
int		surounded(char **matrix, int i, int j, int callback);

// tests.c
void	tests(char **matrix);
void	closed_map(char **matrix, t_cub *data);

// attributes.c
int		ft_nasp(char *str);
int		different(t_attr *attr);
void	next_iter(t_attr *attr);
int		ending_case(t_attr *attr);

// setter_and_init.c
void	set_counter(t_attr *attr, int inc);
void	init_attr(t_attr *attr, char *path);
int		attr_setter(t_attr	*attr, char *ident, char **to_set, int mag);
int		color_setter(t_attr *attr, char *ident, int *to_set, int mag);

// linus_utils2.c
void	freeing_routine(t_attr *attr);
void	freeing_routine_nofd(t_attr *attr);
int		rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
void	wrong_number(t_attr	*attr);
int		all_attributes(int	counter);

// setter_and_init2.c
void	init_fm(t_fm *fm, char *path, int elem);
void	init_go_map(t_gelem *gelem, char *path, int elem);
int		set_attributes(t_cub *data, t_attr attr);

// muated_libft.c
char	*leaktrim(char *s1, char *set);

#endif