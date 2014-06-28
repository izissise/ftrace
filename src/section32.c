/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "symbols.h"

void		*get_section_table32(Elf32_Ehdr *elf, t_file *file)
{
  Elf32_Shdr	*shtable;

  if (!(((void*)&(elf->e_shoff) >= file->data)
        && ((void*)&(elf->e_shoff) <= (file->data + file->size))))
    shtable = file->data;
  else
    shtable = file->data + elf->e_shoff;
  return (shtable);
}

size_t	section_number32(Elf32_Ehdr *elf)
{
  return (elf->e_shnum);
}
