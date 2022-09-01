/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:37:54 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 10:32:34 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	while (i < y - 1)
	{
		ret[i] = malloc(sizeof(char) * x);
		i++;
	}
	return (ret);
}

void	ending_routine(t_gelem *gelem)
{
	while (gelem->line)
	{
		free(gelem->line);
		gelem->line = get_next_line(gelem->fd);
	}
	free(gelem->line);
	close(gelem->fd);
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
	t_gelem	gelem;

	init_go_map(&gelem, path, elem);
	while (gelem.line)
	{
		if (!ft_strncmp(gelem.line, "", 1) \
		|| !ft_strncmp(gelem.line, "\n", 2))
			break ;
		gelem.i++;
		if (ft_strlen(gelem.line) > gelem.max_l)
			gelem.max_l = ft_strlen(gelem.line);
		free(gelem.line);
		gelem.line = get_next_line(gelem.fd);
	}
	ending_routine(&gelem);
	return (create_matrix(gelem.max_l, gelem.i));
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
	t_fm	fm;

	init_fm(&fm, path, elem);
	while (fm.line)
	{
		if (!ft_strncmp(fm.line, "", 1) || \
		!ft_strncmp(fm.line, "\n", 2) || \
		!ft_nasp(fm.line))
			break ;
		fm.line = ft_strtrim(fm.line, "\n");
		ft_strlcpy(matrix[fm.i], fm.line, ft_strlen(fm.line) + 1);
		fm.i++;
		free(fm.line);
		fm.line = get_next_line(fm.fd);
	}
	free(fm.line);
	close(fm.fd);
	matrix[fm.i] = NULL;
	return (matrix);
}

/**
 * @brief Gibt dir einfach die gefüllte Matrix
 * 
 * @param path 
 * @return char** 
 */
char	**get_matrix(char *path, int lines)
{
	char	**matrix;

	matrix = (fill_matrix(get_elem(lines, \
	path), path, \
	lines));
	return (matrix);
}
