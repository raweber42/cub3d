/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:23:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/09/01 13:52:28 by raweber          ###   ########.fr       */
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

int	ft_rstrstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i] && strstr[i][0] != '\n')
		i++;
	return (i);
}

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters && splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	if (splitters)
		free(splitters);
}

void	error_msg(char *msg, t_cub *data, char **matrix)
{
	(void)data;
	if (data)
	{
		if (data->n_path)
			free(data->n_path);
		if (data->w_path)
			free(data->w_path);
		if (data->s_path)
			free(data->s_path);
		if (data->e_path)
			free(data->e_path);
		free(data);
	}
	if (matrix)
	{
		free_all(matrix);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}
