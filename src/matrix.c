/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:37:54 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/29 18:58:28 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	free(splitters);
}

int	elem_cnt(char *path)
{
	int		condition;
	char	c[1];
	int		fd;
	int		digits_per_elem;
	int		digits;
	int		elements;

	elements = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit (1);
	}
	condition = 0;
	digits = 0;
	digits_per_elem = 0;
	if (read(fd, c, 1))//Can be simplified
	{
		digits_per_elem++;
		if (c[0] != '\n')
		{
			elements = 1;
			condition = 1;
		}
	}
	while (read(fd, c, 1))
	{
		digits_per_elem++;
		if (condition == 0 && c[0] != '\n')
		{
			elements = 1;
			condition = 1;
		}
		else if (c[0] == '\n' && condition == 1)
			condition = 2;
		else if (c[0] != '\n' && condition == 2)
			condition = 1;
		else if (c[0] == '\n' && condition == 2)
			condition = 3;
		else if (c[0] == '\n' && condition == 3)
			continue ;
		else if (c[0] != '\n' && condition == 3)
		{
			digits += digits_per_elem;
			digits_per_elem = 0;
			condition = 1;
			elements++;
		}
	}
	close(fd);
	// check_textures(elem_pos[0], path);
	// check_colors(elem_pos[1], path);
	return (digits);
}

char	**create_matrix(int x, int y)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * y);
	i = 0;
	while (i < y)
	{
		ret[i] = malloc(sizeof(char) * x);
		i++;
	}
	return (ret);
}

char	**get_elem(int elem, char *path)
{
	int		fd;
	int		i;
	char	c[1];
	char	*drag;
	char	*line;
	int		max_l;

	fd = open(path, O_RDONLY);
	i = 0;
	drag = NULL;
	while (i < elem)
	{
		read(fd, c, 1);
		i++;
	}
	line = get_next_line(fd);
	max_l = 0;
	i = 1;
	while (line)
	{
		if (!ft_strncmp(drag, "", 1) && !ft_strncmp(line, "", 1))
			break ;
		i++;
		if (ft_strlen(line) > max_l)
			max_l = ft_strlen(line);
		if (drag)
			free(drag);
		drag = line;
		line = get_next_line(fd);
	}
	free(drag);
	free(line);
	return (create_matrix(max_l, i));
}

char	**fill_matrix(char **matrix, char *path, int elem)
{
	int		fd;
	int		i;
	int		j;
	char	c[1];
	char	drag;

	fd = open(path, O_RDONLY);
	i = 0;
	drag = '\0';
	while (i < elem)
	{
		read(fd, c, 1);
		i++;
	}
	i = 0;
	j = 0;
	while (read(fd, c, 1))
	{
		if (c[0] == '\n' && drag == '\n')
			break ;
		if (c[0] == '\n')
		{
			matrix[i][j] = 0;
			i++;
			j = 0;
			drag = 0;
		}
		else
		{
			matrix[i][j] = c[0];
			j++;
			drag = c[0];
		}
	}
	close(fd);
	matrix[i + 1] = NULL;
	return (matrix);
}

char	**get_matrix(char *path)
{
	char	**matrix;
	int	j;

	matrix = (fill_matrix(get_elem\
	(elem_cnt(path), path), path, \
	elem_cnt(path)));

	j = 0;
	while(matrix[j])
	{
		printf("%s\n", matrix[j]);
		j++;
	}
	return (matrix);
}
