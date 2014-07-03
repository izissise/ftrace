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

t_func	*find_symbols_by_addr(t_func **sym_tab, void *addr)
{
  int		i;
  t_func		*tmp;

  printf("%p\n", addr);
  if (!sym_tab)
    return (NULL);
  i = 0;
  while (sym_tab[i])
    {
      tmp = sym_tab[i];
      if (tmp->addr == addr)
        return (tmp);
      i++;
    }
  return (NULL);
}

int		place_symbol_in_graph(void *p1, void *p2)
{
  t_ftrace	*trace;
  t_node	*n;
  t_func	*func;
  t_func	*res;

  n = (t_node*)p1;
  func = (t_func*)n->data;
  trace = (t_ftrace*)p2;
  if ((res = find_symbols_by_addr(trace->symbols_tab, func->addr)))
    {
      free(func->name);
      free(func->binary_name);
      func->name = strdup(res->name);
      func->binary_name = strdup(res->binary_name);
    }
  return (0);
}

void	resolve_symbol(t_ftrace *trace)
{
  apply_on_list(trace->func_list, &place_symbol_in_graph, trace);
}
