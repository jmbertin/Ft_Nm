/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:45:34 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/07 12:45:36 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*src;
	size_t			i;

	i = 0;
	src = (unsigned char *)memoryBlock;
	while (size--)
	{
		if (src[i] == (unsigned char)searchedChar)
			return (src + i);
		i++;
	}
	return (NULL);
}
