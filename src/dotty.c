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

int		print_func_info(void *ptr1, void *ptr2)
{
  t_node	*n;
  t_func	*func;
  int		fd;

  n = (t_node*)ptr1;
  fd = *((int*)ptr2);
  if (!n || !(func = (t_func*)n->data))
    return (1);
  dprintf(fd, "\t%lu [label=\"%s_%p@%s\"];\n", (uint64_t)func->addr,
          func->name, func->addr, func->binary_name);
  return (0);
}

int		print_func_graph(void *ptr1, void *ptr2)
{
  t_node	*n;
  t_func	*func;
  t_func	*tmp;
  int		fd;
  int		i;

  n = (t_node*)ptr1;
  fd = *((int*)ptr2);
  if (!n || !(n->tab) || !(func = (t_func*)n->data))
    return (1);
  i = 0;
  while (n->tab[i])
    {
      if ((tmp = (t_func*)((n->tab[i])->data)))
        dprintf(fd, "\t%lu -> %lu;\n",
                (uint64_t)func->addr, (uint64_t)tmp->addr);
      i++;
    }
  return (0);
}

void		print_graph(t_ftrace *trace)
{
  char		filename[BUFSIZ];
  int		fd;

  snprintf(filename, sizeof(filename), "%s.%s", "funcgraph", "dot");
  if ((fd = open(filename, O_TRUNC | O_CREAT | O_WRONLY, 0666)) == -1)
    return ;
  dprintf(fd, "digraph a {\n");
  apply_on_list(trace->func_list, &print_func_info, &fd);
  apply_on_list(trace->func_list, &print_func_graph, &fd);
  dprintf(fd, "}\n");
  close(fd);
}
