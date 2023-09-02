/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:54 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/09 15:25:29 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * This function reads a 32-bit unsigned integer from the specified memory
 * location `pos` and returns its value. Depending on the endianness specified,
 * the function might reverse the byte order.
 * @param	pos		A pointer to the memory position where the integer is located.
 * @param	endian	An indicator for the endianness of the data.
 * 					ELFDATA2LSB (little endian) or any other value for big endian.
 * @return	The 32-bit unsigned integer value read from the memory.
 */
uint32_t	ft_read_uint32(void *pos, int endian)
{
	if (endian == ELFDATA2LSB)
		return *(uint32_t *)pos;
	else
	{
		uint8_t *p = (uint8_t *)pos;
		return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	}
}

/**
 * This function reads a 16-bit unsigned integer from the specified memory
 * location `pos` and returns its value. Depending on the endianness specified,
 * the function might reverse the byte order.
 * @param	pos		A pointer to the memory position where the integer is located.
 * @param	endian	An indicator for the endianness of the data.
 * 					ELFDATA2LSB (little endian) or any other value for big endian.
 * @return	The 16-bit unsigned integer value read from the memory.
 */
uint16_t	ft_read_uint16(void *pos, int endian)
{
	if (endian == ELFDATA2LSB)
		return *(uint16_t *)pos;
	else
	{
		uint8_t *p = (uint8_t *)pos;
		return (p[0] << 8) | p[1];
	}
}

/**
 * Converts a given value to an [size]-character hexadecimal string.
 * The result string is space-padded to [size] characters for value 0.
 * @param	value	The value to be converted to a hex string.
 * @return	A pointer to the hexadecimal string, or NULL if memory allocation fails.
 */
char	*ft_st_value_to_string(unsigned long long value, int size)
{
	char *hex = malloc((size + 1) * sizeof(char));
	if (!hex)
		return (NULL);

	if (value == 0)
	{
		for (int i = 0; i < size; ++i)
			hex[i] = ' ';
		return (hex);
	}

	for (int i = (size - 1); i >= 0; --i, value >>= 4)
		hex[i] = "0123456789abcdef"[value & 0xF];

	hex[size] = '\0';
	return (hex);
}

/**
 * Compares two characters case-insensitively, considering '_', '.', and '@' as
 * equivalent.
 * @param	a	The first character.
 * @param	b	The second character.
 * @return	The difference between the two characters after converting them to
 * 			lowercase, or 0 if they are equivalent.
 */
static int	tolower_cmp(char a, char b)
{
	if ((a == '_' || a == '.' || a == '@') && (b == '_' || b == '.' || b == '@'))
		return (0);
	return (ft_tolower((unsigned char)a) - ft_tolower((unsigned char)b));
}

/**
 * Compare two strings case-insensitively up to n characters, considering '_',
 * '.', and '@' as equivalent.
 * @param	s1	The first string.
 * @param	s2	The second string.
 * @param	n	The maximum number of characters to be compared.
 * @return	Integer greater than, equal to, or less than 0, if the string s1 is
 *			greater than, equal to, or less than the string s2, respectively.
 */
int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	while (n-- != 0)
	{
		if (tolower_cmp(*s1, *s2) != 0)
			return (tolower_cmp(*s1, *s2));
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
	}
	return 0;
}
