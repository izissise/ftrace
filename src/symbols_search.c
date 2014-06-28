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

void		**list_symbols(t_elf *elf, int sh, t_file *file)
{
  void		**res;
  void		*sect;
  size_t	size;
  int		symsize;
  int		i;

  sect = file->data + elf->sh_offset(elf->elf, sh, file);
  size = elf->sh_size(elf->elf, sh, file);
  if ((sect == file->data) || (size == 0))
    return (NULL);
  i = 0;
  symsize = (elf->type == ELFCLASS32) ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym);
  if ((res = malloc(((size / symsize) + 1) * sizeof(void*))) == NULL)
    return (NULL);
  while ((size_t)(symsize * i) < size)
    {
      res[i] = sect + (symsize * i);
      i++;
    }
  res[i] = NULL;
  return (res);
}

int		find_symbols_by_addr(t_elf *elf, void **symlist,
                           void *addr, t_file *file)
{
  int		i;

  if (!symlist)
    return (-1);
  i = 0;
  while (symlist[i])
    {
      if (elf->symbol_addr(symlist[i], file) == addr)
        return (i);
      i++;
    }
  return (-1);
}
