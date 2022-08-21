/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raweber <raweber@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:55:27 by raweber           #+#    #+#             */
/*   Updated: 2022/08/21 12:57:27 by raweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// The deal_key function handles the user input of different keys.
// If ESC is pressed, the whole program stops.
int	deal_key(int key, t_cub *data)
{
	if (key == 53)
		destroy(data);
	// put key combinations here!
	return (0);
}