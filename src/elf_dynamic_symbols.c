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

void		resolve_elf_dynamic_symbol(t_ftrace *trace, t_elf *elf, t_file *file)
{
  int		sym;
  int		rela;
  void		**rawsym;
  void		**realocsym;
  int		i;
  t_func	*tmp;
  char		*symstr;
  int		symstridx;
  char		*name;

  i = 0;
  if ((rela = find_section(elf, ".rela.plt", 0, file)) != -1)
    {
      if ((realocsym = list_symbols(elf, rela, file, (IS_32(1, 0) ?
                                    sizeof(Elf32_Rel) : sizeof(Elf64_Rel)))))
        while (realocsym[i])
          {
            Elf64_Rel *tmprel = (Elf64_Rel*)realocsym[i];
            if (ELF64_R_TYPE(tmprel->r_info) == R_386_JMP_SLOT)
              {
                printf("0x%lx, 0x%lx\n", tmprel->r_offset, tmprel->r_info);
              }
            i++;
          }
    }
  i = 0;
  if (((sym = find_section(elf, ".dynsym", 0, file)) != -1)
      && ((symstridx = find_section(elf, ".dynstr", 0, file)) != -1)
      && ((symstr = (void*)elf->sh_offset(elf->elf, symstridx, file)) != NULL)
      && ((symstr += (size_t)(file->data))
          < (char*)file->data + (size_t)file->size))
    {
      if ((rawsym = list_symbols(elf, sym, file, (IS_32(1, 0) ?
                                 sizeof(Elf32_Sym) : sizeof(Elf64_Sym)))))
        while (rawsym[i])
          {
            name = elf->symbol_name(rawsym[i], symstr, file);
            tmp->addr = NULL;
            tmp->binary_name = strdup(file->name);
            name = elf->symbol_name(rawsym[i], symstr, file);
            tmp->name = strdup(name ? name : "func");
            trace->symbols_tab = (t_func**)add_ptr_t_tab(
                                   (void**)trace->symbols_tab, (void*)tmp);
            i++;
          }
    }
}
