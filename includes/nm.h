/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:55:48 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/09 15:26:57 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "libft.h"
# include <elf.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

typedef struct s_symbol
{
	char				*name;
	unsigned char		type;
	char				*value;
	struct s_symbol*	next;
}	t_symbol;

/* FT_TOOLS */
uint32_t		ft_read_uint32(void *pos, int endian);
uint16_t		ft_read_uint16(void *pos, int endian);
char			*ft_st_value_to_string(unsigned long long value, int size);
int				ft_strncasecmp(const char *s1, const char *s2, size_t n);

/* FT_STRUCT_TOOLS */
t_symbol		*ft_add_symbol_to_list(t_symbol *list, char *name, unsigned char type, char *value);
void			ft_sort_symbols_by_name(t_symbol *list);
void			ft_print_symbols_list(t_symbol *list, int type, char *filename, int multiple_files);
void			ft_free_symbols_list(t_symbol *list);

/* FT_CHECK */
int				ft_check(int fd, char *filename, int multiple_files);

void			ft_nm32(void *map, char *filename, long unsigned int filesize, int multiple_files);
void			ft_nm64(void *map, char *filename, long unsigned int filesize, int multiple_files);

/* FT_DEFINE_SYMBOL */
unsigned char	ft_define_symbol32(Elf32_Sym *symtab, Elf32_Shdr *o_shdr, int indian);
unsigned char	ft_define_symbol64(Elf64_Sym *symtab, Elf64_Shdr *o_shdr, int endian);

#endif
