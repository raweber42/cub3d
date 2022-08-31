/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:48:03 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 17:48:17 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static size_t	ft_wordlen_helper(const char *s, char c)
{
	size_t	word_len;

	if (!ft_strchr(s, c))
		word_len = ft_strlen(s);
	else
		word_len = ft_strchr(s, c) - s;
	return (word_len);
}

char	**ft_save_split(char *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	word_len;

	if (!s)
		return (0);
	arr = malloc((ft_str_counter(s, c) + 1) * sizeof(char *));
	if (!arr)
	{
		free(s);
		return (0);
	}
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			word_len = ft_wordlen_helper(s, c);
			arr[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	arr[i] = NULL;
	free(s);
	return (arr);
}
