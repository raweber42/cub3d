/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:02:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/30 22:19:35 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	wrong_number(char **splitters, char *line)
{
	if (ft_strstrlen(splitters) != 2)
	{
		free(line);
		free_all(splitters);
		error_msg("Wrong number of attribute values");
	}
}

/**
 * @brief Sets programm parameters
 * 
 * @param path 
 * @param data 
 */
void	set_attributes(char *path, t_cub *data)//Leaking
{
	int		fd;
	char	*line;
	char	**splitters;
	char	**splitters2;
	int		i;
	int		limit;

	limit = elem_cnt(path);
	fd = open(path, O_RDONLY);
	i = 0;
	while (i < limit - 1)
	{
		line = get_next_line(fd);
		splitters = ft_split(leaktrim(line, " \n"), ' ');//Was wenn kein Attributwert gegeben ist?
		if (!ft_strncmp("NO", splitters[0], 3))//Empty line matches for some reason!
		{
			printf("DUNBARS NUMBER[%d]: %d\n", i, ft_strstrlen(splitters));
			printf("THE LINE: %s\n", line);
			wrong_number(splitters, line);
			data->n_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		}
		else if (!ft_strncmp("SO", splitters[0], 3))
		{
			wrong_number(splitters, line);
			data->s_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		}
		else if (!ft_strncmp("WE", splitters[0], 3))
		{
			wrong_number(splitters, line);
			data->w_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		}
		else if (!ft_strncmp("EA", splitters[0], 3))
		{
			wrong_number(splitters, line);
			data->e_path = ft_strtrim(ft_strdup(splitters[1]), "\n");
		}
		else if (!ft_strncmp("F", splitters[0], 2))
		{
			splitters2 = ft_split(leaktrim(line, "F ") , ',');
			if (ft_strstrlen(splitters2) < 3)
			{
				free(line);
				free_all(splitters);
				free_all(splitters2);
				error_msg("You have not defined all color elements\n");
			}
			else if (ft_strstrlen(splitters2) > 3)
			{
				free(line);
				free_all(splitters);
				free_all(splitters2);
				error_msg("Too many color arguments");
			}
			data->f_col = rgb_to_int((unsigned char)ft_atoi(leaktrim(splitters2[1], "\n ,")),//Not segfault save
									(unsigned char)ft_atoi(leaktrim(splitters2[2], "\n ,")),
									(unsigned char)ft_atoi(leaktrim(splitters2[3], "\n ,")));
			free_all(splitters2);
		}
		else if (!ft_strncmp("C", splitters[0], 2))
		{
			splitters2 = ft_split(leaktrim(line, "C "), ',');
			if (ft_strstrlen(splitters2) < 3)
				error_msg("You have not defined all color elements\n");
			else if (ft_strstrlen(splitters2) > 3)
				error_msg("To many color arguments");
			data->c_col = rgb_to_int((unsigned char)ft_atoi(leaktrim(splitters2[1], "\n ,")),//Not segfault save
									(unsigned char)ft_atoi(leaktrim(splitters2[2], "\n ,")),
									(unsigned char)ft_atoi(leaktrim(splitters2[3], "\n ,")));
			free_all(splitters2);
		}
		free_all(splitters);
		free(line);
		i++;
	}
}

void	valid_map(char *path, t_cub *data)
{
	char	**matrix;
	(void)matrix;
	(void)data;

	matrix = get_matrix(path);
	tests(matrix, data);
	closed_map(matrix, data);
	data->world_map = matrix;
	set_attributes(path, data);
}
