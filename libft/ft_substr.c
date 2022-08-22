/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:08:08 by raweber           #+#    #+#             */
/*   Updated: 2022/08/22 13:57:36 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	total_len;
	size_t	counter;

	if (!s)
		return (NULL);
	if (!len || start >= (ft_ft_strlen(s)))
		return (ft_strdup(""));
	substr = malloc(len * sizeof(char) + 1);
	if (substr == 0)
		return (NULL);
	total_len = start + len;
	counter = 0;
	while (start < total_len)
	{
		substr[counter] = s[start];
		start++;
		counter++;
	}
	substr[counter] = 0;
	return (substr);
}
