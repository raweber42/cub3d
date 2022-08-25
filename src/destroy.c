/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:18:46 by raweber           #+#    #+#             */
/*   Updated: 2022/08/25 10:46:05 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Destroys the image, window and frees all allocated memory
int	destroy(t_cub *data, char *str)
{
	if (str)
		ft_printf("%s\n", str);
	if (data->mlx_data->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
	if (data->n_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->n_wall->mlx_img);
	if (data->s_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->s_wall->mlx_img);
	if (data->e_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->e_wall->mlx_img);
	if (data->w_wall->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->w_wall->mlx_img);
	if (data->mlx_data->win_ptr)
		mlx_destroy_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr);
	if (data->mlx_data)
		free(data->mlx_data);
	destroy_wall(data->n_wall);
	destroy_wall(data->s_wall);
	destroy_wall(data->e_wall);
	destroy_wall(data->w_wall);

	//#####################	
	// put more stuff here! (worldmap etc)
	//#####################
	exit(0);
}

void	destroy_wall(t_texture *wall)
{
	int	i;

	i = 0;
	if (wall && wall->matrix)
	{
		while (i < TEXHEIGHT)
			free(wall->matrix[i++]);
		free(wall->matrix);
	}
	if (wall)
		free(wall);
}