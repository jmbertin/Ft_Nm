/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:02 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/10 20:13:19 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * Checks if the ELF magic number is valid for the given ELF header. Must be :
 *  ELFMAG0 == 0x7f
 *  ELFMAG1 == 'E'
 *  ELFMAG2 == 'L'
 *  ELFMAG3 == 'F'
 * @param	ehdr	Pointer to the ELF64 header.
 * @return	Returns 0 if the ELF magic number is valid, otherwise returns 1.
 */
static int	check_elfmag(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[EI_MAG0] != ELFMAG0
		|| ehdr->e_ident[EI_MAG1] != ELFMAG1
		|| ehdr->e_ident[EI_MAG2] != ELFMAG2
		|| ehdr->e_ident[EI_MAG3] != ELFMAG3)
		return (1);
	return (0);
}

/**
 * Validates the EI_VERSION field of the given ELF header.
 * @param	ehdr	Pointer to the ELF64 header.
 * @return	Returns 0 if EI_VERSION matches EV_CURRENT, otherwise returns 1.
 */
static int	check_ei_version(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		return (1);
	return (0);
}

/**
 * Determines and checks the data endianness of the ELF file.
 *  data 0 = error -> Invalid data
 *  data 1 = 2's complement, little endian
 *  data 2 = 2's complement, big endian
 * @param	ehdr	Pointer to the ELF64 header.
 * @param	data	Pointer to store the detected data type (1 little endian, 2 big endian).
 * @return	Returns 1 if a valid data endianness is detected, otherwise returns 0.
 */
static int	check_data(Elf64_Ehdr *ehdr, int *data)
{
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		*data = 1;
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		*data = 2;
	else
		return (0);
	return (1);
}

/**
 * Determines and validates the architecture of the ELF file (32 or 64 bits).
 *  arch 0 = error -> Invalid class
 *  arch 1 = 32 bits
 *  arch 2 = 64 bits
 * @param	ehdr	Pointer to the ELF64 header.
 * @param	arch	Pointer to store the detected architecture type (1 for 32-bit, 2 for 64-bit).
 * @return	Returns 1 if a valid architecture is detected, otherwise returns 0.
 */
static int	check_arch(Elf64_Ehdr *ehdr, int *arch)
{
	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
		*arch = 1;
	else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		*arch = 2;
	else
		return (0);
	return (1);
}

/**
 * Validates a given ELF file by:
 *  Checking its architecture (32 or 64 bits).
 *  Verifying its endianness (little or big endian).
 *  Ensuring its EI_VERSION matches EV_CURRENT.
 *  Confirming its ELF magic number is correct.
 * @param	fd			File descriptor of the ELF file.
 * @param	filename	Name of the ELF file.
 * @return	Returns 0 if the file is a valid ELF file, otherwise returns 1.
 */
int	ft_check(int fd, char *filename, int multiple_files)
{
	void		*map;
	struct stat	st;
	int			arch;
	int			data;

	if (fstat(fd, &st) < 0)
	{
		ft_printf("nm: fstat error\n");
		return (1);
	}

	map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
	{
		ft_printf("nm: mmap error\n");
		return (1);
	}

	if (check_ei_version(map) || check_elfmag(map)
		|| !check_arch(map, &arch) || !check_data(map, &data))
	{
		ft_printf("nm: %s: file format not recognized\n", filename);
		return (1);
	}

	if (arch == 1)
		ft_nm32(map, filename, st.st_size, multiple_files);
	else if (arch == 2)
		ft_nm64(map, filename, st.st_size, multiple_files);

	munmap(map, st.st_size);
	return (0);
}
