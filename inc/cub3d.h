/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:20:10 by raweber           #+#    #+#             */
/*   Updated: 2022/10/21 17:35:29 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if defined(__linux__)
#  include "../minilibx_linux/mlx.h"
# else
#  include "../minilibx_macos/mlx.h"
# endif
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SCREENWIDTH 1000
# define SCREENHEIGHT 1000
# define MOVESPEED 0.45

# if defined(__linux__)

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
# else

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
# endif

enum
{
	FORWARD,
	BACK,
	RIGHT,
	LEFT
};

typedef int		(*t_rec_fun)(char **, int, int);

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
	char		buffer[42];
	char		**r_map;
	int			i;
	char		**splitters;

	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_dir;
	t_vector	perp_dir;
	int			map_x;
	int			map_y;
	t_vector	map_check;
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
	t_list		*free_list;
}				t_cub;

typedef void	(*t_charfun)(char, t_cub *);
typedef void	(*t_coorfun)(char **, int i, int j, t_cub *);

typedef struct s_attr
{
	char	*to_free;
	char	*to_free2;
	int		fd;
	char	*line;
	char	**splitters;
	char	**splitters2;
	int		counter;
	int		i;
	t_cub	*data;
}	t_attr;

typedef struct s_closed
{
	int	i;
	int	limit;
	int	ulimit;
}	t_closed;

typedef struct s_gelem
{
	int		fd;
	int		i;
	char	*line;
	int		max_l;
}	t_gelem;

typedef struct s_fm
{
	int		fd;
	int		i;
	int		j;
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
void	deal_key_3(int key, t_cub *data);

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
void	set_view_direction2(t_cub *data);
int		rgba_to_int(t_color colors);
void	mlx_image_reload(t_cub *data);

// validation.c
void	error_msg(char *msg, t_list *allocated);
void	valid_map(char *path, t_cub *data);
int		surounded(char **matrix, int i, int j, int callback);

// matrix.c
char	**get_matrix(char *path, int lines);
int		elem_cnt(char *path);
void	free_all(char **splitters);

// linus_utils.c
char	**reverse_map(t_cub *data);
int		space_str(char *str);
void	free_all(char **splitters);
char	*leaktrim(char *s1, char *set);
int		ft_strstrlen(char **strstr);
int		ft_rstrstrlen(char **strstr);
void	set_couleur(int *attr, char *value, t_cub *forFree);
void	all_chars(char **strstr, t_charfun toApply, t_cub *data);
void	all_chars2(char **strstr, t_coorfun toApply, t_cub *data);

// recursive_madness.c
void	recursive_closed(char **map, t_closed old, t_cub *data);

// recursive_madness2.c
int		closed_left(char **matrix, int i, int j);
int		closed_up(char **matrix, int i, int j);
int		closed_right(char **matrix, int i, int j);
int		closed_down(char **matrix, int i, int j);
int		surounded(char **matrix, int i, int j, int callback);
void	if_nsurrounded(char **map, int i, int j, t_cub *data);

// attributes.c
int		different(t_attr *attr, t_cub *data);
void	next_iter(t_attr *attr);
int		ending_case(t_attr *attr, t_cub *data);

// setter_and_init.c
void	set_counter(t_attr *attr, int inc);
int		attr_setter(t_attr	*attr, char *ident, char **to_set, int mag);
int		color_setter(t_attr *attr, char *ident, int *to_set, int mag);

// linus_utils2.c
int		free_and_return(char *trimmed_line);
void	freeing_routine(t_attr *attr);
void	freeing_routine_nofd(t_attr *attr);
int		rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
void	wrong_number(t_attr *attr, t_cub *data);
int		all_attributes(int counter);

// setter_and_init2.c
void	init_fm(t_fm *fm, char *path, int elem);
void	init_go_map(t_gelem *gelem, char *path, int elem);
int		set_attributes(t_cub *data, t_attr attr);

// muated_libft.c
char	*leaktrim(char *s1, char *set);

// arg_funcs.c
int		playernum(char c, t_cub	*data);
void	if_wrong_char(char c, t_cub *data);
void	playernum_caller(char c, t_cub	*data);
void	set_player(char **str, int i, int j, t_cub *data);
void	if_0sourrounded(char **matrix, int i, int j, t_cub *data);

// formating.c
void	set_world_map(t_cub *data, char **lines);
char	*file_trimmed(char **av, t_cub *data);
char	**_2dimensions(char *all, t_cub *data);

// _2dimensions.c
char	**_2dalloc(char *all);
void	shift_space_lines(char **lines);
void	shallow_copy(char **lines, char *all);

// attributes.c
void	init_attr(t_cub *data);
void	set_textures(char **lines, t_cub *data);
void	set_colors(char **lines, t_cub *data);
void	check_attributes(t_cub *data);

// tests.c
void	map_closed(char **map, t_cub *data);
void	test_characters(t_cub *data);
void	test_coordinates(t_cub *data);

// parsing.c
void	parsing(t_cub *data, char **av);
void	add_all(char **splitters, t_cub *data);

// garbage.c
void	check_garbage(char **lines, t_cub *data);

#endif