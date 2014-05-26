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
#include "type_map.h"
#include "errno_map.h"

void	handle_error_case(char res[BUFSIZ], long long int rax)
{
  int	err;

  if (rax < 0)
    {
      err = -rax;
      if (err < (int)(sizeof(g_errnomap) / sizeof(char*)))
        snprintf(res, BUFSIZ, "-1 %s (%s)", g_errnomap[err], strerror(err));
    }
}

void	fill_w_type_val(char *type, long long int reg,
                      char res[BUFSIZ], t_strace *trace)
{
  int	i;

  i = 0;
  if (type)
    {
      while (i < (int)(sizeof(g_typemap) / sizeof(t_type_map)))
        {
          if (!strcmp(type, g_typemap[i].type))
            {
              (g_typemap[i].conv)(reg, res, trace);
              return ;
            }
          i++;
        }
      snprintf(res, BUFSIZ, "%s = 0x%lx", type, (long int)reg);
    }
  else
    snprintf(res, BUFSIZ, "%s", "Unknown");
}

void	format_syscall(struct user *infos, t_syscall_info *sys,
                     char restmp[2 * BUFSIZ], t_strace *trace)
{
  int	size;
  int	i;
  int	pos;
  char	*fmt;
  char	*argtmp;

  size = 2 * BUFSIZ;
  pos = 0;
  fmt = "%s";
  i = 0;
  argtmp = trace->argtmp;
  if ((pos += snprintf(restmp, size, "%s(", sys->name)) < size)
    while (sys->args[i])
      {
        size -= pos;
        if (handle_special_syscalls(infos, sys, i, trace))
          fill_w_type_val(sys->args[i], get_param_reg(infos, i),
                          argtmp, trace);
        if ((pos += snprintf(&(restmp[pos]), size - pos, fmt, argtmp)) >= size)
          return ;
        fmt = ", %s";
        i++;
      }
  snprintf(&(restmp[pos]), size - pos, ")");
}

void	print_syscall_ret(int sysnb, struct user *ret, t_strace *trace)
{
  char	rettmp[BUFSIZ];

  if ((sysnb < trace->sizetable) && (sysnb >= 0))
    {
      fill_w_type_val((trace->systable)[sysnb].ret,
                      ret->regs.rax, rettmp, trace);
      handle_error_case(rettmp, ret->regs.rax);
      dprintf(STDERR_FILENO, " = %s\n", rettmp);
    }
}

void			print_syscall(struct user * infos, t_strace * trace)
{
  char			restmp[2 * BUFSIZ];
  int			sysnb;

  sysnb = infos->regs.rax;
  if ((sysnb < trace->sizetable) && (sysnb >= 0))
    {
      format_syscall(infos, &((trace->systable)[sysnb]), restmp, trace);
      dprintf(STDERR_FILENO, "%-39s", restmp);
    }
  else
    dprintf(STDERR_FILENO, "Unknown syscall %d\n", sysnb);
}
