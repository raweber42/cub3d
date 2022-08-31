/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:23:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/31 17:40:34 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static size_t	ft_get_start(char const *str, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{	
		if (ft_strchr(set, str[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_get_end(char const *str, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{	
		if (ft_strchr(set, str[len - i - 1]) == 0)
			return (len - i);
		i++;
	}
	return (len - i);
}

char	*leaktrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	trimmed = malloc(end - start + 1 * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, end - start + 1);
	return (trimmed);
}

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	free(splitters);
}

void	error_msg(char *msg) // sicherstellen, dass immer gefreed wird, falls nötig!
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}
