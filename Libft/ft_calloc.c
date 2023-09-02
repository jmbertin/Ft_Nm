/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:42:37 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/08 10:20:16 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*dest;

	dest = (void *)malloc(elementCount * elementSize);
	if (dest == 0 || elementCount == SIZE_MAX || elementSize == SIZE_MAX)
		return (NULL);
	ft_bzero(dest, elementCount * elementSize);
	return (dest);
}
