/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef NODE_H_INCLUDED
# define NODE_H_INCLUDED

# include <stdlib.h>

# include "tab.h"

typedef struct s_node	t_node;

struct		s_node
{
  void		*data;
  struct s_node	**tab;
};

void	free_node(void *ptr);
void	link_node(t_node *n1, t_node *n2);
int	linked(t_node *n1, t_node *n2);
t_node	*create_node(void *data);

#endif /* !NODE_H_INCLUDED */
