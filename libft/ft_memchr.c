/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 07:51:55 by ncontin           #+#    #+#             */
/*   Updated: 2024/10/23 18:48:46 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*us;
	unsigned char	uc;
	size_t			i;

	i = 0;
	uc = (unsigned char)c;
	us = (unsigned char *)s;
	while (i < n)
	{
		if (us[i] == uc)
			return (&us[i]);
		i++;
	}
	return (0);
}
