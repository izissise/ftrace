/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/vfs.h>

#include "strace.h"

void	trace_void(UNSEDP long long int reg, char res[BUFSIZ],
                 UNSEDP t_strace *trace)
{
  snprintf(res, BUFSIZ, "?");
}

void	trace_chartoiletoile(long long int reg, char res[BUFSIZ],
                           t_strace *trace)
{
  char	*ptr;
  int	j;

  j = 0;
  ptr = NULL;
  while (!peek_proc_data_size(trace->pid, (void*)reg + (j * sizeof(char*)),
                              (void*)(&ptr), sizeof(char*)) && (ptr != NULL))
    j++;
  snprintf(res, BUFSIZ, "[/* %d vars */]", j);
}

void			trace_ststat(long long int reg,
                       char res[BUFSIZ], t_strace *trace)
{
  struct stat	st;

  if (peek_proc_data_size(trace->pid, (void*)reg,
                          (void*)&st, sizeof(struct stat)))
    snprintf(res, BUFSIZ, "0x%lx", (long int)reg);
  else
    snprintf(res, BUFSIZ, "{st_mode=%u, st_size=%u, ...}",
             (int)st.st_mode, (int)st.st_size);
}
