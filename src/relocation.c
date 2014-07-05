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

int		relocation_type(void *rela, t_elf *elf)
{
  Elf64_Rel	*tmprel64;
  Elf32_Rel	*tmprel32;

  tmprel64 = (Elf64_Rel*)rela;
  tmprel32 = (Elf32_Rel*)rela;
  return (IS_32(1, 0) ? ELF32_R_TYPE(tmprel32->r_info)
          : ELF64_R_TYPE(tmprel64->r_info));
}

int		relocation_info(void *rela, t_elf *elf)
{
  Elf64_Rel	*tmprel64;
  Elf32_Rel	*tmprel32;

  tmprel64 = (Elf64_Rel*)rela;
  tmprel32 = (Elf32_Rel*)rela;
  return (IS_32(1, 0) ? ELF32_R_SYM(tmprel32->r_info)
          : ELF64_R_SYM(tmprel64->r_info));
}

void		*relocation_addr(void *rela, t_elf *elf)
{
  Elf64_Rel	*tmprel64;
  Elf32_Rel	*tmprel32;

  tmprel64 = (Elf64_Rel*)rela;
  tmprel32 = (Elf32_Rel*)rela;
  return ((void*)(IS_32(1, 0) ? tmprel32->r_offset : tmprel64->r_offset));
}