/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#ifndef FTRACE_H_INCLUDED
# define FTRACE_H_INCLUDED

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <sys/ptrace.h>
# include <sys/user.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "strace.h"
# include "file.h"
# include "symbols.h"

# define UNSEDP __attribute__((unused))

typedef struct		s_ftrace
{
  pid_t			pid;
  t_elf			elf;
  int			forked;
  int			quit;
  int			sizetable;
  t_syscall_info	*systable;
}			t_ftrace;

char	*prog_full_path(char *prog);
void	trace_pid(t_ftrace *trace);
int	peek_proc_data(pid_t pid, void *addr, short *res, int verbose);
int	peek_proc_data_size(pid_t pid, void *addr, char *res, int size);
int	check_status(pid_t pid);
void	*switch_endian(void *var, int varsize);

#endif /* !FTRACE_H_INCLUDED */
