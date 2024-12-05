/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:55:56 by ncontin           #+#    #+#             */
/*   Updated: 2024/10/23 18:47:24 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(set) - 1;
	while (j >= 0)
	{
		if (set[j] == s1[i])
		{
			i--;
			j = ft_strlen(set) - 1;
		}
		else
			j--;
	}
	i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		j;
	char	*res;
	int		start;
	int		end;

	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	res = malloc(end - start + 1);
	if (!res)
		return (NULL);
	while (start < end)
	{
		res[j] = s1[start];
		j++;
		start++;
	}
	res[j] = '\0';
	return (res);
}
