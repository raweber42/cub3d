/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/22 09:05:37 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

static int	elem_cnt(char *path)
{
	int		condition;
	char	c[1];
	int		fd;
	int		digits_per_elem;
	int		digits;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit (1);
	}
	condition = 0;
	digits = 0;
	digits_per_elem = 0;
	if (read(fd, c, 1))
	{
		digits_per_elem++;
		if (c[0] != '\n')
			condition = 1;
	}
	while (read(fd, c, 1))
	{
		digits_per_elem++;
		if (condition == 0 && c[0] != '\n')
			condition = 1;
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
		}
		
	}
	close(fd);
	return (digits - 1);
}

static int	get_elem(int num, char *path)
{
	int	fd;
	int	i;
	char c[1];

	fd = open(path, O_RDONLY);
	i = 0;
	while (i < num)
	{
		read(fd, c, 1);
		i++;
	}
	return (fd);
}

void	valid_map(char *path)
{
	int		fd;
	char	*line;
	char	*dragging;
	int		i;

	fd = get_elem(elem_cnt(path), path);
	line = get_next_line(fd);
	dragging = NULL;
	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '0')
				error_msg("Map is not closed");
			i++;
		}
	}
	while (line)
	{
		if (!line[0])
			break ;
		if (line[0] == '0' ||  line[ft_strlen(line) - 2] == '0')
			error_msg("Map is not closed");
		dragging = line;
		line = get_next_line(fd);
	}
	i = 0;
	if (dragging)
	{
		while (dragging[i])
		{
			if (dragging[i] == '0')
				error_msg("Map is not closed");
			i++;
		}
	}
	close(fd);
}
