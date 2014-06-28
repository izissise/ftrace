/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#include "ftrace.h"

void	func_info(t_func *func, void *addr, t_ftrace *trace)
{
  int	symbol;
  char	*tmp;
  void	*sym;

  func->addr = addr;
  free(func->binary_name);
  free(func->name);
  symbol = find_symbols_by_addr(&trace->elf, trace->symbols_list,
                                addr, &trace->file);
  if (symbol == -1)
    {
      func->binary_name = strdup("a.out");
      func->name = strdup("func");
      return ;
    }
  sym = trace->symbols_list[symbol];
  tmp = trace->elf.symbol_name(sym, trace->symstr, &trace->file);
  func->name = strdup(tmp ? tmp : "func");
}

void	free_info(t_func *func)
{
  if (func)
    {
      free(func->binary_name);
      free(func->name);
    }
}
