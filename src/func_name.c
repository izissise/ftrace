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
  func->addr = addr;
  free(func->binary_name);
  func->binary_name = strdup("a.out");
  free(func->name);
  func->name = strdup("func");
}

void	free_info(t_func *func)
{
  if (func)
    {
      free(func->binary_name);
      free(func->name);
    }
}
