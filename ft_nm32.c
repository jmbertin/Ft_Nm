/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:36 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/09 15:06:31 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * Reads the symbol table of an ELF32 file, retrieves each symbol's name and
 * type, and adds it to a list of symbols. It returns the updated symbols list.
 * @param	map					A pointer to the mapped ELF32 file in memory.
 * @param	symbol_table_header	A pointer to the symbol table header.
 * @param	section_headers		A pointer to the array of section headers in the ELF32 file.
 * @param	o_sec				A pointer to the section headers.
 * @param	symbols				A pointer to the current symbols list.
 * @return	The updated list of symbols after processing the symbol table.
 */
static t_symbol	*process_symbol_table(void *map, Elf32_Shdr *symbol_table_header, Elf32_Shdr *section_headers, Elf32_Shdr *o_sec, t_symbol *symbols)
{
	int			endian = ((Elf32_Ehdr *)map)->e_ident[EI_DATA];
	Elf32_Sym	*symbol_table = (Elf32_Sym *) ((char *) map + symbol_table_header->sh_offset);
	Elf32_Shdr	*strtab_header = &section_headers[symbol_table_header->sh_link];
	char		*strtab = (char *) map + strtab_header->sh_offset;

	for (long unsigned int i = 0; i < symbol_table_header->sh_size / sizeof(Elf32_Sym); ++i)
	{
		Elf32_Sym		*symbol = &symbol_table[i];
		char			*symbol_name = strtab + symbol->st_name;
		unsigned char	symbol_type = ft_define_symbol32(symbol, o_sec, endian);

		if (symbol->st_name == 0)
			continue;

		if (symbol_type == 'U')
			symbols = ft_add_symbol_to_list(symbols, ft_strdup(symbol_name), symbol_type, ft_st_value_to_string(0, 8));
		else
			symbols = ft_add_symbol_to_list(symbols, ft_strdup(symbol_name), symbol_type, ft_st_value_to_string(symbol->st_value, 8));
	}

	return symbols;
}

/**
 * Reads an ELF32 file, identifies its symbol table, and processes it to retrieve
 * and print the symbols it contains. If no symbols are found, a corresponding
 * message is printed.
 * @param	map				A pointer to the mapped ELF32 file in memory.
 * @param	filename		The name of the ELF32 file being processed.
 * @param	filesize		The size of the ELF32 file in bytes.
 * @param	multiple_files	Flag to indicate if there are multiple files to process.
 */
void	ft_nm32(void *map, char *filename, long unsigned int filesize, int multiple_files)
{
	Elf32_Ehdr	*elf_header = (Elf32_Ehdr *) map;
	Elf32_Shdr	*section_headers = (Elf32_Shdr *) ((char *) map + elf_header->e_shoff);
	Elf32_Shdr	*o_sec = section_headers;
	Elf32_Shdr	*symbol_table_header = NULL;

	if (elf_header->e_shoff > filesize)
	{
		ft_printf("nm: %s: no symbols\n", filename);
		return;
	}

	for (long unsigned int i = 0; i < elf_header->e_shnum; ++i)
	{
		Elf32_Shdr	*section_header = &section_headers[i];

		if (section_header->sh_type == SHT_SYMTAB)
			symbol_table_header = section_header;
	}

	if (symbol_table_header == NULL)
	{
		ft_printf("nm: %s: no symbols\n", filename);
		return;
	}

	t_symbol	*symbols = NULL;

	if (symbol_table_header != NULL)
		symbols = process_symbol_table(map, symbol_table_header, section_headers, o_sec, symbols);

	ft_sort_symbols_by_name(symbols);
	ft_print_symbols_list(symbols, 32, filename, multiple_files);
	ft_free_symbols_list(symbols);
}
