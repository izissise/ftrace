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

int			check_valid_elf(t_file *file)
{
  Elf32_Ehdr		*elf;
  unsigned char	*e_ident;

  if (file->size < sizeof(Elf32_Ehdr))
    return (1);
  elf = (Elf32_Ehdr*)file->data;
  e_ident = (unsigned char*)(&(elf->e_ident));
  if (!((e_ident[EI_MAG0] == ELFMAG0)
        && (e_ident[EI_MAG1] == ELFMAG1)
        && (e_ident[EI_MAG2] == ELFMAG2)
        && (e_ident[EI_MAG3] == ELFMAG3)))
    {
      dprintf(STDERR_FILENO, "%s: File format not recognized\n", file->name);
      return (1);
    }
  if (((elf->e_type == ELFCLASS64) && (file->size < sizeof(Elf64_Ehdr)))
      || ((elf->e_type == ELFCLASS32) && (file->size < sizeof(Elf32_Ehdr))))
    return (1);
  return (0);
}

int	init_elf(t_elf *elf, t_file *file)
{
  elf->elf = file->data;
  elf->type = ((Elf32_Ehdr*)(elf->elf))->e_ident[EI_CLASS];
  if (!((elf->type == ELFCLASS32) || (elf->type == ELFCLASS64)))
    return (1);
  elf->get_section_table = IS_32(&get_section_table32, &get_section_table64);
  elf->section_number = IS_32(&section_number32, &section_number64);
  elf->symbols_str = IS_32(&symbols_str_32, &symbols_str_64);
  elf->symbol_name = IS_32(&symbol_name32, &symbol_name64);
  elf->symbol_type = IS_32(&symbol_type32, &symbol_type64);
  elf->symbol_addr = IS_32(&symbol_addr32, &symbol_addr64);
  elf->sh_offset = IS_32(&sh_offset32, &sh_offset64);
  elf->sh_size = IS_32(&sh_size32, &sh_size64);
  elf->sh_addr = IS_32(&sh_addr32, &sh_addr64);
  elf->sh_section_name = IS_32(&sh_section_name32, &sh_section_name64);
  elf->sh_type = IS_32(&sh_type32, &sh_type64);
  elf->check_elf_size = IS_32(&check_elf_size32,
                              &check_elf_size64);
  return (0);
}

void		resolve_elf_static_symbol(t_ftrace *trace, t_elf *elf, t_file *file)
{
  int		sym;
  char		*symstr;
  void		**rawsym;
  int		i;
  t_func	*tmp;
  char		*name;

  i = 0;
  if (((sym = find_section(elf, ".symtab", 0, file)) != -1)
      && ((symstr = elf->symbols_str(elf->elf, sym, file)) != NULL))
    {
      if ((rawsym = list_symbols(elf, sym, file)))
        while (rawsym[i] && ((tmp = malloc(sizeof(t_func))) != NULL))
          {
            tmp->addr = elf->symbol_addr(rawsym[i], file);
            tmp->binary_name = strdup(file->name);
            name = elf->symbol_name(rawsym[i], symstr, file);
            tmp->name = strdup(name ? name : "func");
            trace->symbols_tab = (t_func**)add_ptr_t_tab(
                                   (void**)trace->symbols_tab,
                                   (void*)tmp);
            i++;
          }
      free(rawsym);
    }
}

int		load_elf(char *path, t_ftrace *trace)
{
  t_elf	*elf;
  t_file	*file;

  if (((elf = malloc(sizeof(t_elf))) == NULL)
      || ((file = malloc(sizeof(t_file))) == NULL))
    {
      free(elf);
      return (1);
    }
  if ((open_file(file, path, O_RDONLY, 0) == -1)
      || check_valid_elf(file)
      || init_elf(elf, file)
      || elf->check_elf_size(elf->elf, file))
    {
      free(elf);
      close_file(file);
      return (1);
    }
  elf->elf = file->data;
  trace->elf = (t_elf**)add_ptr_t_tab((void**)trace->elf, (void*)elf);
  trace->file = (t_file**)add_ptr_t_tab((void**)trace->file, (void*)file);
  resolve_elf_static_symbol(trace, elf, file);
  return (0);
}
