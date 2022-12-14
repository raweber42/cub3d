/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:46:12 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 10:47:04 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != 0)
	{
		len++;
	}
	return (len);
}
