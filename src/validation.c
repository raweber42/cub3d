/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/29 16:59:02 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg) // sicherstellen, dass immer gefreed wird, falls nötig!
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

static int	allowed_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	valid_left(char **matrix, int i, int j)
{
	if (j == 0)
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	return (valid_left(matrix, i, j - 1));
}

int	valid_right(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1])
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	return (valid_right(matrix, i, j + 1));
}

int	closed_left(char **matrix, int i, int j)
{
	if (j == 0 || matrix[i][j - 1] == '1')
		return (1);
	else if (matrix[i][j - 1] != ' ')
		return (0);
	else
		return (surounded(matrix, i, j - 1, 2));
}

int	closed_up(char **matrix, int i, int j)
{
	if (i == 0 || matrix[i - 1][j] == '1')
		return (1);
	else if (matrix[i - 1][j] != ' ')
		return (0);
	else
		return (surounded(matrix, i - 1, j, 3));
}

int	closed_right(char **matrix, int i, int j)
{
	if (!matrix[i][j + 1] || matrix[i][j + 1] == '1')
		return (1);
	else if (matrix[i][j + 1] != ' ')
		return (0);
	else
		return (surounded(matrix, i, j + 1, 0));
}

int	closed_down(char **matrix, int i, int j)
{
	if (!matrix[i + 1] || matrix[i + 1][j] == '1')
		return (1);
	else if (matrix[i + 1][j] != ' ')
		return (0);
	else
		return (surounded(matrix, i + 1, j, 1));
}

int	surounded(char **matrix, int i, int j, int callback)
{
	int	iter;
	const rec_fun	fun_arr[5] = {closed_left, closed_up, closed_right, closed_down};

	iter = 0;
	while (iter < 4)
	{
		if (callback == iter)
		{
			iter++;
			continue;
		}
		if (!fun_arr[iter](matrix, i, j))
			return (0);
		iter++;
	}
	return (1);
}

int	valid_space(char **matrix, int i, int j)
{
	if (matrix[i][j] == ' ')
	{
		if (valid_left(matrix, i, j) || valid_right(matrix, i, j))
			return (1);
		if (surounded(matrix, i, j, -1))
			return (1);
		error_msg("Map contains spaces");
	}
	return (0);
}

void	tests(char **matrix, t_cub *data)
{
	int	i;
	int	j;

	(void)data;
	i = 0;
	j = 0;
	while (matrix[i])
	{
		while(matrix[i][j])
		{
			if (valid_space(matrix, i, j))
			{
				j++;
				continue ;
			}
			if (!allowed_char(matrix[i][j]))
				error_msg("Map contains invalid character");
			if ((i == 0 && matrix[i][j] != '1') \
				|| (!matrix[i + 1] && matrix[i][j] != '1')
				|| (j == 0 && matrix[i][j] != '1')
				|| (!matrix[i][j + 1] && matrix[i][j] != '1'))
				error_msg("Map not surrounded by ones");
			j++;
		}
		j = 0;
		i++;
	}
}

void	closed_map(char **matrix, t_cub *data)
{
	int	i;
	int	j;
	int	player;
	int	limit;
	int	ulimit;

	i = 0;
	j = 0;
	player = 0;
	while (matrix[i])
	{
		if (i > 0)
			limit = ft_strlen(matrix[i - 1]);
		if (matrix[i + 1])
			ulimit = ft_strlen(matrix[i  + 1]);
		while(matrix[i][j])
		{
			if (matrix[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (i > 0 && j >= limit && matrix[i][j] != '1')
				error_msg("Map is not closed");
			if (matrix[i + 1] && j >= ulimit && matrix[i][j] != '1')
				error_msg("Map is not closed");
			if (matrix[i][j] == 'N' || \
				matrix[i][j] == 'E' || \
				matrix[i][j] == 'W' || \
				matrix[i][j] == 'S')
			{
				data->pos.x = i;
				data->pos.y = j;
				data->orientation = matrix[i][j];
				matrix[i][j] = '0';
				if (player == 1)
					error_msg("This is not coop");
				player = 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player == 0)
		error_msg("You are not that lonley");
}

void	check_access(t_cub *data)
{
	if (!data->n_path)
		error_msg("Give north texture");
	if (!data->s_path)
		error_msg("Give south texture");
	if (!data->w_path)
		error_msg("Give west texture");
	if (!data->e_path)
		error_msg("Give east texture");
}

void	null_textures(t_cub *data)
{
	data->n_path = NULL;
	data->s_path = NULL;
	data->w_path = NULL;
	data->e_path = NULL;
}

void	check_textures(int *elem, char *path, t_cub *data)
{
	int		fd;
	int		_read;
	char	c[1];
	char	*line;
	char	**splitters;
	int		i;

	null_textures(data);
	fd = open(path, O_RDONLY);
	_read = 0;
	while (_read < elem[0] && read(fd, c, 1))
		_read++;
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		splitters = ft_split(line, ' ');
		free(line);
		if (!ft_strncmp("NO", splitters[0], 2))
			data->n_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		else if (!ft_strncmp("SO", splitters[0], 2))
			data->s_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		else if (!ft_strncmp("WE", splitters[0], 2))
			data->w_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		else if (!ft_strncmp("EA", splitters[0], 2))
			data->e_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		else
			error_msg("Direction identifier expected in first block");
		free_all(splitters);
		i++;
	}
	check_access(data);
}

void	check_celling(int *elem, char *path, t_cub *data)
{
	int	i;
	int	fd;

	fd = open(path, O_RDONLY);
	i = 0;
	while (i < elem[1] && read(fd, c, 1))
}

void	valid_map(char *path, t_cub *data)
{
	char	**matrix;

	matrix = get_matrix(path);
	tests(matrix, data);
	closed_map(matrix, data);
	data->world_map = matrix;
	check_textures(elem_cnt(path), path, data);
	check_celling(elem_cnt(path), path, data);
}
