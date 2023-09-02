/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:02:44 by jbertin           #+#    #+#             */
/*   Updated: 2022/12/03 18:50:32 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*gnl_joinbuff(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (0);
	res = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(*res));
	if (res == 0)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	j = i;
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	free (s1);
	return (res);
}

char	*gnl_buffclean(char *buff_static)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	while (buff_static[i] && buff_static[i] != '\n')
		i++;
	if (!buff_static[i])
	{
		free (buff_static);
		return (NULL);
	}
	buffer = ft_calloc((ft_strlen(buff_static) - i + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	i++;
	while (buff_static[i])
		buffer[j++] = buff_static[i++];
	buffer[j] = '\0';
	free (buff_static);
	return (buffer);
}

char	*gnl_parse(char *buff_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff_static[i])
		return (NULL);
	while (buff_static[i] && buff_static[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buff_static[i] && buff_static[i] != '\n')
	{
		line[i] = buff_static[i];
		i++;
	}
	if (buff_static[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_read(int fd, char *buff_static)
{
	char	*buffer;
	int		length;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	length = 1;
	while (!ft_strchr(buff_static, '\n') && length != 0)
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if (length == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[length] = '\0';
		buff_static = gnl_joinbuff(buff_static, buffer);
	}
	free (buffer);
	return (buff_static);
}

char	*get_next_line(int fd)
{
	static char	*buff_static[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (0);
	buff_static[fd] = gnl_read(fd, buff_static[fd]);
	if (!buff_static[fd])
		return (NULL);
	line = gnl_parse(buff_static[fd]);
	buff_static[fd] = gnl_buffclean(buff_static[fd]);
	return (line);
}
