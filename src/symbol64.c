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

char		*symbols_str_64(Elf64_Ehdr *elf, int sym, t_file *file)
{
  Elf64_Shdr	*tab;
  char		*res;

  if (((tab = get_section_table64(elf, file)) == NULL)
      || ((void*)(tab + sym) > file->data + file->size)
      || ((void*)(&(tab[tab[sym].sh_link])) > file->data + file->size))
    return (NULL);
  res = file->data + (tab[tab[sym].sh_link]).sh_offset;
  if ((void*)res > file->data + file->size)
    return (NULL);
  return (res);
}

char	*symbol_name64(Elf64_Sym *sym, char *symstr, t_file *file)
{
  if (((void*)(symstr + sym->st_name) >= file->data + file->size)
      || (symstr[sym->st_name] == '\0'))
    return (NULL);
  return (&symstr[sym->st_name]);
}
