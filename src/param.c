/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#include "strace.h"

long long int	get_param_reg(struct user *info, int parameter)
{
  long long int	regs[6];

  memset(regs, 0, sizeof(regs));
  regs[0] = info->regs.rdi;
  regs[1] = info->regs.rsi;
  regs[2] = info->regs.rdx;
  regs[3] = info->regs.rcx;
  regs[4] = info->regs.r8;
  regs[5] = info->regs.r9;
  if (parameter > 5 || parameter < 0)
    return (0);
  return (regs[parameter]);
}