/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#ifndef STRACE_H_INCLUDED
# define STRACE_H_INCLUDED

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

# define UNSEDP __attribute__((unused))
# define BINARY32 0
# define BINARY64 1

# define MAXFLAGSSYSCALLSPEC 30

typedef struct	s_strace t_strace;

typedef struct	s_syscall_info
{
  char		*name;
  char		*ret;
  char		*args[9];
}		t_syscall_info;

typedef struct	s_type_map
{
  char		*type;
  void		(*conv)(long long int reg, char res[BUFSIZ], t_strace *trace);
}		t_type_map;

typedef struct	s_special_print
{
  char		*name;
  int		arg;
  struct
  {
    int		flags;
    char		*str;
  }		flags[MAXFLAGSSYSCALLSPEC];
}		t_special_print;

typedef struct		s_strace
{
  pid_t			pid;
  int			forked;
  int			quit;
  int			bit;
  int			sizetable;
  t_syscall_info	*systable;
  char			argtmp[BUFSIZ];
}			t_strace;

char	*prog_full_path(char *prog);

void	trace_pid(t_strace *trace);
int	peek_proc_data(pid_t pid, void *addr, short *res, int verbose);
int	peek_proc_data_size(pid_t pid, void *addr, char *res, int size);
int	check_status(pid_t pid);
void	*switch_endian(void *var, int varsize);
void	print_syscall(struct user *infos, t_strace *trace);
void	print_syscall_ret(int sysnb, struct user *ret, t_strace *trace);
long long int	get_param_reg(struct user *info, int parameter);
int	is_64_bit(int fd);
int	is_64_bit_pid(pid_t pid);
int	is_64_bit_path(const char *path);
int	handle_special_syscalls(struct user *infos, t_syscall_info *sys,
                            int arg, t_strace *trace);

void	trace_int(long long int reg, char res[BUFSIZ], t_strace *trace);
void	trace_uint(long long int reg, char res[BUFSIZ], t_strace *trace);
void	trace_chartoile(long long int reg, char res[BUFSIZ], t_strace *trace);
void	trace_ptrtoile(long long int reg, char res[BUFSIZ], t_strace *trace);
void	trace_ssizet(long long int reg, char res[BUFSIZ], t_strace *trace);
void	trace_void(UNSEDP long long int reg, char res[BUFSIZ],
                 UNSEDP t_strace *trace);
void	trace_size_t(long long int reg, char res[BUFSIZ], UNSEDP t_strace *trace);
void	trace_chartoiletoile(long long int reg, char res[BUFSIZ],
                           t_strace *trace);
void	trace_ststat(long long int reg,
                   char res[BUFSIZ], t_strace *trace);

#endif /* !STRACE_H_INCLUDED */
