/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "node.h"

t_node	*create_node(void *data)
{
  t_node	*res;

  if ((res = malloc(1 * sizeof(*res))) == NULL)
    return (NULL);
  res->data = data;
  res->tab = NULL;
  return (res);
}

int	linked(t_node *n1, t_node *n2)
{
  t_node	*tmp;
  int	i;

  i = 0;
  if (n1->tab != NULL)
    while ((tmp = (t_node*)n1->tab[i]) != NULL)
      {
        if (tmp == n2)
          return (1);
        i++;
      }
  return (0);
}

void	link_node(t_node *n1, t_node *n2)
{
  if (!linked(n1, n2))
    n1->tab = (t_node**)add_ptr_t_tab((void**)n1->tab, (void*)n2);
  return (0);
}

void	free_node(void *ptr)
{
  t_node	*n;

  n = (t_node*)ptr;
  if (n)
    free(n->tab);
  free(n);
}
