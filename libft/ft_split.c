/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:00:25 by ncontin           #+#    #+#             */
/*   Updated: 2024/10/23 18:48:14 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	is_word;
	int	counter;

	i = 0;
	is_word = 1;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (is_word == 1)
			{
				counter++;
				is_word = 0;
			}
		}
		else
			is_word = 1;
		i++;
	}
	return (counter);
}

static int	find_word_len(char const *s, char c, int s_index)
{
	int	word_len;

	word_len = 0;
	while (s[s_index + word_len] != c && s[s_index + word_len])
		word_len++;
	return (word_len);
}

static int	fill_words(char const *s, char c, int s_index, char *array)
{
	int	len;

	len = 0;
	while (s[s_index] != c && s[s_index])
	{
		array[len] = s[s_index];
		len++;
		s_index++;
	}
	array[len] = '\0';
	return (s_index);
}

static void	*free_mem(int i, char **array)
{
	while (i > 0)
	{
		free(array[i - 1]);
		i--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		s_index;
	char	**array;

	i = 0;
	s_index = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (i < words)
	{
		while (s[s_index] == c)
			s_index++;
		array[i] = malloc(find_word_len(s, c, s_index) + 1);
		if (!(array[i]))
			return (free_mem(i, array));
		s_index = fill_words(s, c, s_index, array[i]);
		i++;
	}
	return (array);
}
