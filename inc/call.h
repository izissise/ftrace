/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#ifndef CALL_H_INCLUDED
# define CALL_H_INCLUDED

typedef struct	s_func
{
  void		*addr;
  char		*name;
  char		*binary_name;
}		t_func;

void	func_info(t_func *func, void *addr, t_ftrace *trace);
void	free_info(t_func *func);

#endif /* !CALL_H_INCLUDED */
