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

void	trace_int(long long int reg, char res[BUFSIZ],
                UNSEDP t_strace *trace)
{
  snprintf(res, BUFSIZ, "%ld", (long int)reg);
}

void	trace_uint(long long int reg, char res[BUFSIZ],
                 UNSEDP t_strace *trace)
{
  snprintf(res, BUFSIZ, "%lu", (unsigned long int)reg);
}

void	trace_chartoile(long long int reg, char res[BUFSIZ], t_strace *trace)
{
  char	str[60];
  int	i;

  i = 0;
  memset(str, 0, sizeof(str));
  while (i < (int)sizeof(str) - 1)
    {
      if (peek_proc_data_size(trace->pid, (void*)reg + i, &(str[i]), 1)
          || (str[i] == '\0'))
        break;
      i++;
    }
  str[i] = '\0';
  if (i > 0)
    {
      if (i == (sizeof(str) - 1))
        snprintf(res, BUFSIZ, "\"%s\"...", str);
      else
        snprintf(res, BUFSIZ, "\"%s\"", str);
    }
  else
    snprintf(res, BUFSIZ, "0x%lx", (long int)reg);
}

void	trace_ptrtoile(long long int reg, char res[BUFSIZ],
                     UNSEDP t_strace *trace)
{
  snprintf(res, BUFSIZ, "0x%lx", (long int)reg);
}
