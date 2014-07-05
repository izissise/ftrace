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
#include "ftrace.h"

char		**elf_dyna_symb_tab(t_elf *elf, t_file *file)
{
  void		**rawsym;
  int		sym;
  int		i;
  char		*name;
  char		*symstr;
  int		symstridx;
  char		**res;

  i = -1;
  res = NULL;
  rawsym = NULL;
  if (((sym = find_section(elf, ".dynsym", 0, file)) != -1)
      && ((symstridx = find_section(elf, ".dynstr", 0, file)) != -1)
      && ((symstr = (void*)elf->sh_offset(elf->elf, symstridx, file)) != NULL)
      && ((symstr += (size_t)(file->data))
          < (char*)file->data + (size_t)file->size))
    if ((rawsym = (list_symbols(elf, sym, file, (IS_32(1, 0) ?
                                sizeof(Elf32_Sym) : sizeof(Elf64_Sym))))))
      while (rawsym[++i])
        if ((name = elf->symbol_name(rawsym[i], symstr, file)))
          res = (char**)add_ptr_t_tab((void**)res, name);
  free(rawsym);
  return (res);
}

t_func		*fill_tab_dyna_symbol(void *realocsym, char **rawsym,
                                void *pltraddr, t_elf *elf)
{
  int		rela;
  t_func		*tmp;
  char		*name;

  rela = relocation_info(realocsym, elf);
  if ((tmp = malloc(sizeof(t_func))))
    {
      name = rawsym[relocation_info(realocsym, elf)];
      tmp->addr = (void*)((size_t)pltraddr + (rela * 0x10));
      tmp->name = strdup(name ? name : "func");
      // printf("name: %s, addr: %p\n", tmp->name, tmp->addr);
      return (tmp);
    }
  return (NULL);
}

void		resolve_elf_dynamic_symbol(t_ftrace *trace,
                                   t_elf *elf, t_file *file)
{
  int		rela;
  char		**rawsym;
  void		**realocsym;
  void		*pltraddr;
  int		i;
  int		rawsize;
  t_func		*tmp;

  pltraddr = NULL;
  if ((rela = find_section(elf, ".plt", 0, file)) != -1)
    pltraddr = (void*)elf->sh_addr(elf->elf, rela, file);
  i = -1;
  rawsym = elf_dyna_symb_tab(elf, file);
  if (((rela = find_section(elf, ".rela.plt", 0, file)) != -1) && rawsym)
    {
      rawsize = ptr_tab_size((void**)rawsym);
      if ((realocsym = list_symbols(elf, rela, file, (IS_32(1, 0) ?
                                    sizeof(Elf32_Rel) : sizeof(Elf64_Rel)))))
        while (realocsym[++i])
          if ((rela = relocation_info(realocsym[i], elf)) < rawsize
              && rela >= 0 && (tmp = fill_tab_dyna_symbol(realocsym[i], rawsym,
                                     pltraddr, elf)))
            {
              tmp->binary_name = strdup(file->name);
              trace->symbols_tab = (t_func**)add_ptr_t_tab(
                                     (void**)trace->symbols_tab, (void*)tmp);
            }
    }
  free(realocsym);
  free(rawsym);
}
