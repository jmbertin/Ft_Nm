/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:50:07 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/09 08:44:23 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_is_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_dest_len(char const *s1, char const *set)
{
	int	i;
	int	end;
	int	length;

	i = 0;
	length = ft_strlen(s1);
	end = length - 1;
	while (s1[i] && ft_is_charset(s1[i], set) == 1)
		i++;
	while (ft_is_charset(s1[end], set) == 1 && end > 0)
		end--;
	if (end < i)
		return (0);
	if (end == i)
		return (1);
	else
		return (end - i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		length;
	char	*trimmed;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (0);
	length = ft_dest_len(s1, set);
	trimmed = (char *)malloc(sizeof(char) * length + 1);
	if (trimmed == 0)
		return (NULL);
	while (ft_is_charset(s1[i], set) == 1)
		i++;
	while (s1[i] && length > 0)
	{
		trimmed[j] = s1[i];
		i++;
		j++;
		length--;
	}
	trimmed[j] = '\0';
	return (trimmed);
}
