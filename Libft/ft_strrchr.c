/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:49:49 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/07 12:49:50 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	end;

	end = ft_strlen(string);
	searchedChar = (unsigned char) searchedChar;
	while (end >= 0)
	{
		if (string[end] == searchedChar)
			return ((char *)string + end);
		end--;
	}
	return (0);
}
