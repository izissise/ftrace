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

#include "special_syscallparam.h"

void	print_spec_syscall_param(long long int reg, t_special_print *flags,
                               char *argtmp)
{
  int	i;
  int	nbflags;
  int	pos;
  int	size;

  i = 0;
  nbflags = 0;
  pos = 0;
  size = BUFSIZ;
  while (flags->flags[i].str)
    {
      if ((reg & flags->flags[i].flags) || (reg == flags->flags[i].flags))
        {
          if ((pos += snprintf(&(argtmp[pos]), size - pos, (nbflags ? "|%s"
                               : "%s"), flags->flags[i].str)) >= size)
            return ;
          nbflags++;
        }
      i++;
    }
}

void	print_write_byte(char *argtmp, void *ptr, int size, t_strace *trace)
{
  char	str[60];
  int	i;
  int	pos;
  int	c;

  size = (size > (int)sizeof(str) - 1) ? (int)sizeof(str) - 1 : size;
  pos = 0;
  c = 0;
  i = 0;
  while (i < size && pos < size)
    {
      if (peek_proc_data_size(trace->pid, ptr + i, (void*)&c, 1))
        break ;
      pos += isprint(c) ? snprintf(&(str[pos]), size - pos, "%c", c)
             : snprintf(&(str[pos]), size - pos, "\\%03o", c);
      i++;
    }
  if (i > 0)
    {
      (i == (sizeof(str) - 1)) ? snprintf(argtmp, BUFSIZ, "\"%s\"...", str)
      : snprintf(argtmp, BUFSIZ, "\"%s\"", str);
    }
  else
    snprintf(argtmp, BUFSIZ, "0x%lx", (long int)ptr);
}

int			handle_special_syscalls(struct user *infos, t_syscall_info *sys,
                                int arg, t_strace *trace)
{
  char			*argtmp;
  long long int	reg;
  int			i;

  argtmp = trace->argtmp;
  reg = get_param_reg(infos, arg);
  i = 0;
  if (!strcmp(sys->name, "write") && (arg == 1))
    {
      print_write_byte(argtmp, (void*)reg, get_param_reg(infos, 2), trace);
      return (0);
    }
  while (i < (int)(sizeof(g_special_print) / sizeof(t_special_print)))
    {
      if (!strcmp(sys->name ? sys->name : "", g_special_print[i].name)
          && (arg == g_special_print[i].arg))
        {
          print_spec_syscall_param(reg, &(g_special_print[i]), argtmp);
          return (0);
        }
      i++;
    }
  return (1);
}
