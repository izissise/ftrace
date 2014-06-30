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

t_node	*find_node_func_f_list(t_list *func_list, void *call)
{
  t_node	*n;
  t_func	*f;

  while (func_list)
    {
      if (((n = (t_node*)(func_list->data)))
          && ((f = (t_func*)(n->data))))
        {
          if (f->addr == call)
            return (n);
        }
      func_list = func_list->next;
    }
  return (NULL);
}

t_node	*find_func(void *call, t_ftrace *trace)
{
  t_node	*res;
  t_func	*func;

  res = find_node_func_f_list(trace->func_list, call);
  if (res)
    return (res);
  if (((res = create_node(NULL)) == NULL)
      || ((func = func_info(call, trace)) == NULL))
    {
      free(res);
      return (NULL);
    }
  res->data = func;
  add_to_list_top(&(trace->func_list), res);
  return (res);
}

void		destroy_node_func(void *ptr)
{
  t_node	*n;

  n = (t_node*)ptr;
  if (n)
    {
      free_info((t_func*)(n->data));
      free_node(n);
    }
}

