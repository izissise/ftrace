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

typedef struct s_node	t_node;

struct		s_node
{
  void		*data;
  struct s_node	**tab;
};

#endif /* !NODE_H_INCLUDED */
