/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:50:17 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/09 18:12:18 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static size_t	ft_min(size_t len, size_t size_s)
{
	if (len > size_s)
		return (size_s);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	size_s;

	i = 0;
	if (!s)
		return (0);
	size_s = ft_strlen(s);
	if ((len == 0 && start != 0) || start > size_s)
	{
		dest = (char *)malloc(sizeof(char));
		dest[i] = '\0';
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * (ft_min(len, size_s) + 1));
	if (dest == 0)
		return (0);
	while (i < len && i < size_s)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
