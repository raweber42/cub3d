/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:18:46 by raweber           #+#    #+#             */
/*   Updated: 2022/08/21 13:02:13 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Destroys the image, window and frees all allocated memory
int	destroy(t_cub *data)
{
	if (data->mlx_data->mlx_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->mlx_img);
	if (data->mlx_data->win_ptr)
		mlx_destroy_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr);
	//#####################	
	// put more stuff here!
	//#####################
	exit(0);
}
