/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:37:54 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/30 21:33:27 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief gives the line number, at whicht the map starts
 * 
 * @param path the file, that contains the map
 * @return int (line number)
 */
int	elem_cnt(char *path)
{
	char	*line;
	int		fd;
	int		result;
	int		chunck;
	int		condition;

	fd = open(path, O_RDONLY);
	result = 0;
	condition = 0;
	chunck = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "\n", 2))
			condition = 1;
		else if (condition && ft_strncmp(line, "\n", 1))
		{
			condition = 0;
			result = chunck;
		}
		chunck++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (result);
}

/**
 * @brief Create a matrix object (malloced)
 * 
 * @param x the number of columns (including the null)
 * @param y the number of lines (including the NULL)
 * @return char** matrix (malloced!)
 */
char	**create_matrix(int x, int y)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (y + 1));
	i = 0;
	while (i < y)
	{
		ret[i] = malloc(sizeof(char) * x);
		i++;
	}
	return (ret);
}

/**
 * @brief Misst die Maße für die Matrix | Linenumber, bei der die matrix anfängt
 * 
 * @param elem Linenumber
 * @param path File, in der die Matrix steht
 * @return char** Returns (recursivley) a matrix object
 */
char	**get_elem(int elem, char *path)
{
	int		fd;
	int		i;
	char	*line;
	int		max_l;

	fd = open(path, O_RDONLY);
	i = 0;
	while (i < elem)
	{
		free(get_next_line(fd));
		i++;
	}
	line = get_next_line(fd);
	max_l = 0;
	i = 0;
	while (line)
	{
		if (!ft_strncmp(line, "", 1) || !ft_strncmp(line, "\n", 2))
			break ;
		i++;
		if (ft_strlen(line) > max_l)
			max_l = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (create_matrix(max_l, i));
}

/**
 * @brief Fills the matrix object with content
 * 
 * @param matrix 
 * @param path 
 * @param elem Linenumber, bei der die Matrix steht
 * @return char** Filled matrix
 */
char	**fill_matrix(char **matrix, char *path, int elem)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(path, O_RDONLY);
	i = 0;
	while (i < elem - 1)
	{
		free(get_next_line(fd));
		i++;
	}
	i = 0;
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "", 1) || !ft_strncmp(line, "\n", 2))
			break ;
		line = ft_strtrim(line, "\n");
		ft_strlcpy(matrix[i], line, ft_strlen(line) + 1);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	matrix[i] = NULL;
	return (matrix);
}


/**
 * @brief Gibt dir einfach die gefüllte Matrix
 * 
 * @param path 
 * @return char** 
 */
char	**get_matrix(char *path)
{
	char	**matrix;

	matrix = (fill_matrix(get_elem\
	(elem_cnt(path), path), path, \
	elem_cnt(path)));

	return (matrix);
}
