/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:50 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/09 14:49:39 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * Prints out symbols from the given list based on their types (32 or 64).
 * If `multiple_files` is set, the filename will be printed as a header.
 * @param	list			A pointer to the first t_symbol in the list.
 * @param	type			Specifies the type (32 bits / 64 bits) of the list.
 * @param	filename		The name of the file containing the symbols.
 * @param	multiple_files	A flag indicating if there are multiple files.
 */
void	ft_print_symbols_list(t_symbol *list, int type, char *filename, int multiple_files)
{
	t_symbol	*tmp;

	if (multiple_files)
		ft_printf("\n%s:\n", filename);

	for (tmp = list; tmp; tmp = tmp->next)
	{
		if (type == 32)
		{
			if (tmp->type == 'w')
				ft_printf("         %c %s\n", tmp->type, tmp->name);
			else if (tmp->type != 'A' && tmp->type != 'w')
				ft_printf("%s %c %s\n", tmp->value, tmp->type, tmp->name);
			else if (tmp->type == 'A' && ft_strncmp(tmp->value, "        ", 8) != 0)
				ft_printf("%s %c %s\n", tmp->value, tmp->type, tmp->name);
		}
		else if (type == 64)
		{
			if (tmp->type == 'U')
				ft_printf("                 %c %s\n", tmp->type, tmp->name);
			else if (tmp->type == 'A' && ft_strncmp(tmp->value, "                ", 16) == 0)
				continue;
			else if (tmp->type != 'T' && tmp->type != 'U' && tmp->type != 'b')
				ft_printf("%s %c %s\n", tmp->value, tmp->type, tmp->name);
			else if ((tmp->type == 'T' || tmp->type == 'b') && ft_strncmp(tmp->value, "                ", 16) != 0)
				ft_printf("%s %c %s\n", tmp->value, tmp->type, tmp->name);
			else if ((tmp->type == 'T' || tmp->type == 'b') && ft_strncmp(tmp->value, "                ", 16) == 0)
				ft_printf("0000000000000000 %c %s\n", tmp->type, tmp->name);
		}
	}
}

/**
 * Appends a new symbol to the provided list.
 * @param	list	A pointer to the first t_symbol in the list.
 * @param	name	The name of the symbol.
 * @param	type	The type of the symbol.
 * @param	value	The value of the symbol.
 * @returns	The head of the symbols list.
 */
t_symbol	*ft_add_symbol_to_list(t_symbol *list, char *name, unsigned char type, char *value)
{
	t_symbol	*new_symbol = malloc(sizeof(t_symbol));
	if (new_symbol == NULL)
	{
		ft_printf("Error allocating memory\n");
		return NULL;
	}

	new_symbol->name = name;
	new_symbol->type = type;
	new_symbol->value = value;
	new_symbol->next = NULL;

	if (list == NULL)
		return (new_symbol);
	else
	{
		t_symbol *tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_symbol;
		return (list);
	}
}

/**
 * Frees all the memory occupied by the symbols list.
 * @param	list	A pointer to the first t_symbol in the list.
 */
void	ft_free_symbols_list(t_symbol *list)
{
	t_symbol	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

/**
 * Removes underscores, dots, and '@' symbols from a string.
 * @param	str	The original string.
 * @return	A new string without underscores, dots, and '@' symbols.
 */
static char	*clean_string(char *str)
{
	int		j = 0;
	char	*new_str = malloc(ft_strlen(str) + 1);
	if (new_str == NULL)
	{
		ft_printf("Error allocating memory\n");
		return (NULL);
	}

	for(int i = 0; str[i]; i++)
	{
		if(str[i] != '_' && str[i] != '.' && str[i] != '@')
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';

	return (new_str);
}

/**
 * Sorts symbols by their name, considering symbol names with
 * and without underscores, in a case-insensitive manner. If names are equal,
 * it further sorts them based on their type.
 * @param	list	A pointer to the first t_symbol in the list.
 */
void	ft_sort_symbols_by_name(t_symbol *list)
{
	t_symbol	*tmp;
	char		*tmp_name;
	char		tmp_type;
	char		*tmp_value;
	int			sorted = 0;

	while (!sorted)
	{
		sorted = 1;
		for (tmp = list; tmp->next; tmp = tmp->next)
		{
			char	*name1 = clean_string(tmp->name);
			char	*name2 = clean_string(tmp->next->name);
			int		comparison = 0;

			if (ft_strncmp(name1, name2, INT_MAX) == 0 && ft_strncmp(tmp->name, tmp->next->name, INT_MAX) != 0)
				comparison = ft_strncmp(tmp->name, tmp->next->name, INT_MAX);
			else
			{
				comparison = ft_strncasecmp(name1, name2, INT_MAX);
				if (tmp->type == tmp->next->type)
				{
					if (ft_strncasecmp(tmp->name, tmp->next->name, INT_MAX) == 0)
						comparison = ft_strncmp(tmp->name, tmp->next->name, INT_MAX) * -1;
				}
			}

			if (comparison > 0 || (comparison == 0 && tmp->type > tmp->next->type))
			{
				tmp_name = tmp->name;
				tmp_type = tmp->type;
				tmp_value = tmp->value;

				tmp->name = tmp->next->name;
				tmp->type = tmp->next->type;
				tmp->value = tmp->next->value;

				tmp->next->name = tmp_name;
				tmp->next->type = tmp_type;
				tmp->next->value = tmp_value;

				sorted = 0;
			}
			free(name1);
			free(name2);
		}
	}
}
