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
# include "get_next_line.h"
# include "file.h"
# include "symbols.h"
# include "call.h"
# include "liste.h"
# include "node.h"
# include "tab.h"

# define UNSEDP __attribute__((unused))
# define MAYALIAS __attribute__((__may_alias__))

# define GRAPHFILENAME "funcgraph.dot"

typedef struct		s_ftrace
{
  pid_t			pid;
  t_elf			**elf;
  t_file			**file;
  int			forked;
  int			quit;
  int			sizetable;
  t_syscall_info	*systable;
  t_func			**symbols_tab;
  const char		*symstr;
  t_list			*func_list;
  t_list			*func_stack;
}			t_ftrace;

char	*prog_full_path(char *prog);
void	trace_pid(t_ftrace *trace, t_elf *elf);
int	peek_proc_data(pid_t pid, void *addr, short *res, int verbose);
int	peek_proc_data_size(pid_t pid, void *addr, char *res, int size);
int	check_status(pid_t pid);
void	*switch_endian(void *var, int varsize);
int	load_elf(char *path, t_ftrace *trace, int64_t addroffset);

void	load_libs_symbols(t_ftrace *trace);

void		resolve_elf_dynamic_symbol(t_ftrace *trace, t_elf *elf,
                                   t_file *file, int64_t addrofset);

inline int	is_ret_opcode(unsigned short opcode);
inline int	is_call_opcode(unsigned short opcode);
void		*calc_call(unsigned short opcode, struct user *infos,
                   pid_t pid, unsigned short extended);
inline void	*call_ff_case(struct user *infos, pid_t pid,
                          char instr[15], unsigned short extended);

uint64_t	three_bit_register(struct user *infos, uint8_t tbit);

t_node	*find_func(void *call, t_ftrace *trace);
t_node	*find_func_name(char *name, t_ftrace *trace);
t_func	*find_symbols_by_addr(t_func **sym_tab, void *addr);
t_func	*create_func_infos(void *addr, char *name, char *binary_name);
void		destroy_node_func(void *ptr);

void		resolve_symbol(t_ftrace *trace);
void		print_graph(t_ftrace *trace);

#endif /* !FTRACE_H_INCLUDED */
