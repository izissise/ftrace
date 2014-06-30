/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Dec 13 13:14:01 2012 Hugues
*/

#include "liste.h"

t_list	*find_in_list(t_list *begin, void *data)
{
  t_list	*list;

  list = begin;
  while (list != NULL)
    {
      if (list->data == data)
        return (list);
      list = list->next;
    }
  return (NULL);
}

void		add_to_list_top(t_list **begin, void *data)
{
  t_list	*tmp;

  tmp = NULL;
  if (*begin != NULL)
    tmp = *begin;
  if ((*begin = malloc(1 * sizeof(t_list))) == NULL)
    {
      *begin = tmp;
      return ;
    }
  (*begin)->data = data;
  (*begin)->next = tmp;
}
