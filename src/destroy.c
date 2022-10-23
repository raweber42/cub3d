/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:18:46 by raweber           #+#    #+#             */
/*   Updated: 2022/10/20 19:43:28 by ljahn            ###   ########.fr       */
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
	exit(0);
}

// Destroys the image, window and frees all allocated memory
int	destroy_no_msg(t_cub *data)
{
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
	exit(0);
}

void	destroy_wall(t_texture *wall)
{
	int	i;

	i = 0;
	if (wall && wall->matrix)
	{
		while (i < TEXHEIGHT && wall->matrix[i])
			free(wall->matrix[i++]);
		if (wall->matrix)
			free(wall->matrix);
	}
}
