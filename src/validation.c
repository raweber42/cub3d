/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/22 14:26:59 by ljahn            ###   ########.fr       */
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
	int		fd;
	int		i;
	char	c[1];
	char	drag;
	int		pipus[2];

	pipe(pipus);
	fd = open(path, O_RDONLY);
	i = 0;
	drag = 0;
	while (i < num)
	{
		read(fd, c, 1);
		i++;
	}
	while (read(fd, c, 1))
	{
		if (drag == '\n' && c[0] == '\n')
			break ;
		write(pipus[1], c, 1);
		drag = c[0];
	}
	close(fd);
	close(pipus[1]);
	return (pipus[0]);
}

// static int	allowed_char(char c)
// {
// 	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n')
// 		return (1);
// 	return (0);
// }

// void	invalid_chars(int fd)
// {
// 	char	*line;
// 	int		i;
// 	int		last_len;

// 	line = get_next_line(fd);
// 	last_len = 0;
// 	while (line)
// 	{	
// 		if (line[0] == '\n')
// 			break;
// 		if (last_len != 0 && !(ft_strlen(line) >= last_len - 1 && ft_strlen(line) <= last_len + 1))
// 		{
// 			printf("LAST LEN: %d\n", last_len);
// 			printf("THE COMPARE LEN: %d\n", ft_strlen(line));
// 			error_msg("Unclosed map");
// 		}
// 		last_len = ft_strlen(line);
// 		i = 0;
// 		while (line[i])
// 		{
// 			if (!allowed_char(line[i]))
// 				error_msg("Map contains invalid characters");
// 			i++;
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// }

void	valid_map(char *path)
{
	int		fd;
	// char	*line;
	// char	*dragging;
	int		i;
	int		chunck;
	char	c[1];

	// invalid_chars(get_elem(elem_cnt(path), path));
	fd = get_elem(elem_cnt(path), path);
	c[0] = 0;
	chunck = 0;
	i = 0;
	while (pread(fd, c, 1, i))
	{
		if (c[0] == '\n')
		{
			printf("WIDTH: %d\n", chunck);
			chunck = 0;
		}
		chunck++;
		i++;
	}
	// line = get_next_line(fd);
	// dragging = NULL;
	// i = 0;
	// if (line)
	// {
	// 	while (line[i])
	// 	{
	// 		if (line[i] != '1' && line[i] != '\n')
	// 			error_msg("Map is not closed");
	// 		i++;
	// 	}
	// }
	// while (line)
	// {
	// 	if (line[0] == '\n')
	// 		break ;
	// 	if (line[0] != '1' ||  line[ft_strlen(line) - 2] != '1')
	// 		error_msg("Map is not closed");
	// 	dragging = line;
	// 	line = get_next_line(fd);
	// }
	// i = 0;
	// if (dragging)
	// {
	// 	while (dragging[i])
	// 	{
	// 		if (dragging[i] != '1' && dragging[i] != '\n')
	// 			error_msg("Map is not closed");
	// 		i++;
	// 	}
	// }
	// close(fd);
	exit(0);
}
