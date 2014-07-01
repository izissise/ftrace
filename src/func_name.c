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

t_func	*func_info(void *addr, t_ftrace *trace)
{
  t_func	*func;
  int		symbol;
  char		*tmp;
  void		*sym;

  if ((func = malloc(sizeof(t_func))) == NULL)
    return (NULL);
  func->addr = addr;
  symbol = find_symbols_by_addr(&trace->elf, trace->symbols_list,
                                addr, &trace->file);
  func->binary_name = strdup(trace->file.name);
  if (symbol == -1)
    {
      func->name = strdup("func");
      return (func);
    }
  sym = trace->symbols_list[symbol];
  tmp = trace->elf.symbol_name(sym, trace->symstr, &trace->file);
  func->name = strdup(tmp ? tmp : "func");
  return (func);
}

t_func	*create_func_infos(void *addr, char *name, char *binary_name)
{
  t_func	*func;

  if ((func = malloc(sizeof(t_func))) == NULL)
    return (NULL);
  func->addr = addr;
  func->name = strdup(name);
  func->binary_name = strdup(binary_name);
  return (func);
}

void	free_info(t_func *func)
{
  if (func)
    {
      free(func->binary_name);
      free(func->name);
      free(func);
    }
}
