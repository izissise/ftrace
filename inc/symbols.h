/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef SYMBOLS_H_INCLUDED
# define SYMBOLS_H_INCLUDED

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <elf.h>
# include "file.h"

# define IS_32(x, y) ((elf->type == ELFCLASS32) ? (void*)(x) : (void*)(y))
# define ABS(x) ((x < 0) ? -(x) : (x))

struct		s_elf;
typedef struct	s_elf t_elf;

struct		s_elf
{
  int		type;
  void		*elf;
  void		*(*get_section_table)();
  size_t	(*section_number)();
  size_t	(*sh_offset)();
  size_t	(*sh_size)();
  size_t	(*sh_addr)();
  size_t	(*sh_type)();
  char		*(*sh_section_name)();
  char		*(*symbols_str)();
  char		*(*symbol_name)();
};

void		*deref(void *addr, t_file *file);
int		check_valid_elf(t_file *file);
int		init_elf(t_elf *elf, t_file *file);
int		find_section(t_elf *elf, const char *section,
                   int start, t_file *file);
int		find_section_type(t_elf *elf, uint32_t type,
                        int start, t_file *file);

void		*get_section_table64(Elf64_Ehdr *elf, t_file *file);
size_t		section_number64(Elf64_Ehdr *elf);
char		*symbols_str_64(Elf64_Ehdr *elf, int sym, t_file *file);
char		*symbol_name64(Elf64_Sym *sym, char *symstr, t_file *file);
size_t		sh_offset64(Elf64_Ehdr *elf, int idx, t_file *file);
size_t		sh_size64(Elf64_Ehdr *elf, int idx, t_file *file);
size_t		sh_addr64(Elf64_Ehdr *elf, int idx, t_file *file);
uint32_t	sh_type64(Elf64_Ehdr *elf, int idx, t_file *file);
char		*sh_section_name64(Elf64_Ehdr *elf, int idx, t_file *file);
char		symbol_sect_type64(Elf64_Ehdr *elf, Elf64_Sym *sym,
                           t_file *file);
char		symclass_type64(Elf64_Ehdr *elf, Elf64_Sym *sym, t_file *file);

void		*get_section_table32(Elf32_Ehdr *elf, t_file *file);
size_t		section_number32(Elf32_Ehdr *elf);
char		*symbols_str_32(Elf32_Ehdr *elf, int sym, t_file *file);
char		*symbol_name32(Elf32_Sym *sym, char *symstr, t_file *file);
size_t		sh_offset32(Elf32_Ehdr *elf, int idx, t_file *file);
size_t		sh_size32(Elf32_Ehdr *elf, int idx, t_file *file);
size_t		sh_addr32(Elf32_Ehdr *elf, int idx, t_file *file);
uint32_t	sh_type32(Elf32_Ehdr *elf, int idx, t_file *file);
char		*sh_section_name32(Elf32_Ehdr *elf, int idx, t_file *file);
char		symbol_sect_type32(Elf32_Ehdr *elf, Elf32_Sym *sym,
                           t_file *file);
char		symclass_type32(Elf32_Ehdr *elf, Elf32_Sym *sym, t_file *file);

#endif /* !SYMBOLS_H_INCLUDED */
