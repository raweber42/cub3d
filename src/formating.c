/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:58:37 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/21 18:12:50 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_world_map(t_cub *data, char **lines)
{
	int	first_map;
	int	j;

	first_map = ft_strstrlen(lines) - 1;
	while (first_map >= 0 && ft_strncmp(lines[first_map], "", 1))
		first_map--;
	first_map++;
	data->world_map = ft_calloc(ft_strstrlen(&lines[first_map]) \
	+ 1, sizeof(char *));
	j = 0;
	while (lines[first_map])
		data->world_map[j++] = lines[first_map++];
	data->world_map[j] = NULL;
	ft_lstadd_back(&data->free_list, ft_lstnew(data->world_map));
}

static void	bad_file_descriptor(void)
{	
	perror("File could not be open");
	exit(1);
}

char	*file_trimmed(char **av, t_cub *data)
{
	char	*trimmed_all;
	char	*all;
	int		total;
	int		fd;
	int		old_total;

	fd = open(av[1], O_RDONLY);
	total = read(fd, data->buffer, 42);
	old_total = 0;
	if (fd == -1)
		bad_file_descriptor();
	while (old_total < total)
	{
		old_total = total;
		total += read(fd, data->buffer, 42);
	}
	close(fd);
	all = malloc(total + 1);
	fd = open(av[1], O_RDONLY);
	read(fd, all, total);
	close(fd);
	all[total] = '\0';
	trimmed_all = ft_strtrim(all, " \n");
	ft_lstadd_back(&data->free_list, ft_lstnew(trimmed_all));
	return (trimmed_all);
}

char	**_2dimensions(char *all, t_cub *data)
{
	char	**lines;

	lines = _2dalloc(all);
	shallow_copy(lines, all);
	shift_space_lines(lines);
	ft_lstadd_back(&data->free_list, ft_lstnew(lines));
	return (lines);
}
