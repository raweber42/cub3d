/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/22 19:42:30 by ljahn            ###   ########.fr       */
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
	char		**matrix;

	matrix = get_matrix(path);
	exit(0);
}
