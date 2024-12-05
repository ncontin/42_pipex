/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:23:08 by ncontin           #+#    #+#             */
/*   Updated: 2024/10/23 18:48:34 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dst_ptr;
	char	*src_ptr;
	size_t	i;

	i = 0;
	dst_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dst_ptr > src_ptr)
	{
		while (n-- > 0)
			dst_ptr[n] = src_ptr[n];
	}
	else
	{
		while (i < n)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
