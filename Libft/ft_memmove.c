/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:46:00 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/07 12:46:02 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)destination;
	s = (unsigned char *)source;
	if (!destination && !source)
		return (destination);
	if (source < destination)
	{
		while (size--)
			d[size] = s[size];
	}
	else
	{
		while (size--)
			*d++ = *s++;
	}
	return (destination);
}
