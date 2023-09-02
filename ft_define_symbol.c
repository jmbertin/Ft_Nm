/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:30 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/10 17:12:41 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * Evaluates the provided symbol table and section header to decide the type of
 * the symbol (like 'T', 'U', 'W', etc.). These symbols are representative of
 * the symbol's attributes, such as its binding, type, section header index,
 * and section header flags.
 * @param	symtab	Pointer to the ELF32 symbol table entry.
 * @param	o_shdr	Pointer to the section header table.
 * @param	endian	Endianness of the ELF file (0 for little endian, 1 for big endian).
 * @return	Returns a character representing the symbol type.
 */
unsigned char	ft_define_symbol32(Elf32_Sym *symtab, Elf32_Shdr *o_shdr, int endian)
{
	uint16_t		st_shndx = ft_read_uint16(&symtab->st_shndx, endian);
	unsigned int	bind = ELF32_ST_BIND(symtab->st_info);
	unsigned int	type = ELF32_ST_TYPE(symtab->st_info);
	Elf32_Shdr		*related_shdr = &o_shdr[st_shndx];

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return (st_shndx == SHN_UNDEF) ? 'v' : 'V';
		return (st_shndx == SHN_UNDEF) ? 'w' : 'W';
	}

	if (st_shndx == SHN_COMMON) return 'C';

	if (st_shndx == SHN_UNDEF) return 'U';

	if (st_shndx == SHN_ABS)
		return ((type == STT_OBJECT) && (bind == STB_LOCAL)) ? 'a' : 'A';

	if (related_shdr->sh_type == SHT_PROGBITS)
	{
		if (related_shdr->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			return (bind == STB_LOCAL) ? 't' : 'T';
		else if (related_shdr->sh_type == SHT_PROGBITS && (related_shdr->sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
			return (bind == STB_LOCAL) ? 'd' : 'D';
		else if (related_shdr->sh_flags == SHF_ALLOC)
			return (bind == STB_LOCAL) ? 'r' : 'R';
	}

	if (related_shdr->sh_type == SHT_NOBITS && (related_shdr->sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
		return (bind == STB_LOCAL) ? 'b' : 'B';

	if (((related_shdr->sh_type == SHT_NOTE && related_shdr->sh_flags == SHF_ALLOC) ||
		(related_shdr->sh_type == SHT_FINI_ARRAY || related_shdr->sh_type == SHT_INIT_ARRAY || related_shdr->sh_type == SHT_DYNAMIC)) && related_shdr->sh_flags != 2) // exclude related_shdr->sh_flags != 2
		return (bind == STB_LOCAL) ? 'd' : 'D';

	if (related_shdr->sh_type == SHT_INIT_ARRAY || related_shdr->sh_type == SHT_FINI_ARRAY || related_shdr->sh_type == SHT_PREINIT_ARRAY)
		return (bind == STB_LOCAL) ? 'b' : 'B';
	else
		return (bind == STB_LOCAL) ? 'r' : 'R'; // add the else condition

	return '?';
}

/**
 * Evaluates the provided symbol table and section header to decide the type of
 * the symbol (like 'T', 'U', 'W', etc.). These symbols are representative of
 * the symbol's attributes, such as its binding, type, section header index, and
 * section header flags.
 * @param	symtab	Pointer to the ELF64 symbol table entry.
 * @param	o_shdr	Pointer to the section header table.
 * @param	endian	Endianness of the ELF file (0 for little endian, 1 for big endian).
 * @return	Returns a character representing the symbol type.
 */
unsigned char	ft_define_symbol64(Elf64_Sym *symtab, Elf64_Shdr *o_shdr, int endian)
{
	uint16_t		st_shndx = ft_read_uint16(&symtab->st_shndx, endian);
	unsigned int	bind = ELF64_ST_BIND(symtab->st_info);
	unsigned int	type = ELF64_ST_TYPE(symtab->st_info);
	Elf64_Shdr		*related_shdr = o_shdr + symtab->st_shndx;

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return (st_shndx == SHN_UNDEF) ? 'v' : 'V';
		return (st_shndx == SHN_UNDEF) ? 'w' : 'W';
	}

	else if (st_shndx == SHN_COMMON) return ('C');

	else if (st_shndx == SHN_ABS) return ('A');

	else if (st_shndx == SHN_UNDEF) return ('U');

	else if (related_shdr->sh_type == SHT_PROGBITS
		|| related_shdr->sh_type == SHT_FINI_ARRAY
		|| related_shdr->sh_type == SHT_INIT_ARRAY
		|| related_shdr->sh_type == SHT_DYNAMIC)
	{
		if (related_shdr->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			return (bind == STB_LOCAL) ? 't' : 'T';

		else if (related_shdr->sh_flags == (SHF_ALLOC | SHF_WRITE))
			return (bind == STB_LOCAL) ? 'd' : 'D';

		else if (related_shdr->sh_flags == SHF_ALLOC)
			return (bind == STB_LOCAL) ? 'r' : 'R';
	}

	else if (related_shdr->sh_type == SHT_NOBITS && (related_shdr->sh_flags == (SHF_ALLOC | SHF_WRITE) || type == SHT_DYNAMIC))
		return (bind == STB_LOCAL) ? 'b' : 'B';

	if (type == STT_OBJECT && st_shndx == 23) return 'D';

	if (bind == STB_GLOBAL || bind == STB_LOCAL)
		return (bind == STB_LOCAL) ? 'r' : 'R';

	return '?';
}
