/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/29 20:01:11 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

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

int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	set_attributes(char *path, t_cub *data)//Leaking
{
	int		fd;
	char	*line;
	char	**splitters;
	char	**splitters2;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		splitters = ft_split(line, ' ');
		if (ft_strstrlen(splitters) < 2)
		{
			// free(line);
			line = get_next_line(fd);
			// free_all(splitters);
			continue ;
		}
		if (!ft_strncmp("NO", splitters[0], 3))
		{
			data->n_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
			// free_all(splitters);
		}
		else if (!ft_strncmp("SO", splitters[0], 3))
		{
			data->s_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
			// free_all(splitters);
		}
		else if (!ft_strncmp("WE", splitters[0], 3))
		{
			data->w_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
			// free_all(splitters);
		}
		else if (!ft_strncmp("EA", splitters[0], 3))
		{
			data->e_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
			// free_all(splitters);
		}
		else if (!ft_strncmp("F", splitters[0], 2))
		{
			splitters2 = ft_split(ft_strtrim(line, "F "), ',');
			if (ft_strstrlen(splitters2) < 3)
				error_msg("You have not defined all color elements\n");
			data->f_col = rgb_to_int((unsigned char)ft_atoi(ft_strtrim(splitters2[1], "\n ,")),//Not segfault save
									(unsigned char)ft_atoi(ft_strtrim(splitters2[2], "\n ,")),
									(unsigned char)ft_atoi(ft_strtrim(splitters2[3], "\n ,")));
			// free_all(splitters);
			// free_all(splitters2);
		}
		else if (!ft_strncmp("C", splitters[0], 2))
		{
			splitters2 = ft_split(ft_strtrim(line, "C "), ',');
			if (ft_strstrlen(splitters2) < 3)
				error_msg("You have not defined all color elements\n");
			data->c_col = rgb_to_int((unsigned char)ft_atoi(ft_strtrim(splitters2[1], "\n ,")),//Not segfault save
									(unsigned char)ft_atoi(ft_strtrim(splitters2[2], "\n ,")),
									(unsigned char)ft_atoi(ft_strtrim(splitters2[3], "\n ,")));
			// free_all(splitters);
			// free_all(splitters2);
		}
		else
		{
			free(splitters);
			free(line);
		}
		// free(line);
		line = get_next_line(fd);
	}
}

void	valid_map(char *path, t_cub *data)
{
	char	**matrix;

	matrix = get_matrix(path);
	tests(matrix, data);
	closed_map(matrix, data);
	data->world_map = matrix;
	set_attributes(path, data);
}
