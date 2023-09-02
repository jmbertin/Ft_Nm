/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:47:23 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/09 08:33:25 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static void	ft_strpcpy(char *dest, char *src, int size, int poz)
{
	int	i_src;
	int	i;

	i_src = poz;
	i = 0;
	while (i_src < poz + size)
	{
			dest[i] = src[i_src];
			i++;
			i_src++;
	}
	dest[size - 1] = '\0';
}

static int	ft_is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	ft_n_str(char *str, char sep)
{
	size_t	i;
	int		n_str;

	i = 0;
	n_str = 0;
	while (str[i])
	{
		while (ft_is_sep(str[i], sep) == 1 && str[i])
			i++;
		if (i < ft_strlen(str))
			n_str++;
		while (ft_is_sep(str[i], sep) == 0 && str[i])
			i++;
	}
	return (n_str);
}

static void	ft_exec_split(char const *s, char c, char **strs)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && j < ft_n_str((char *)s, c))
	{
		while (ft_is_sep(s[i], c) == 1 && s[i])
			i++;
		while (ft_is_sep(s[i], c) == 0 && s[i])
		{
			i++;
			k++;
		}
		strs[j] = malloc(sizeof(char) * k + 1);
		ft_strpcpy(strs[j], (char *)s, k + 1, i - k);
		j++;
		k = 0;
	}
	strs[ft_n_str((char *)s, c)] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	strs = (char **)malloc(sizeof(char *) * (ft_n_str((char *)s, c) + 1));
	if (!strs)
		return (NULL);
	ft_exec_split(s, c, strs);
	return (strs);
}
