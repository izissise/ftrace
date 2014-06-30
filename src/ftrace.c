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
#include "syscall_x86_x64.h"
#include "syscall_x86.h"

void			call_instruction(t_ftrace *trace, struct user *infos,
                           short opcode, int extended)
{
  t_node		*upnode;
  t_node		*node;
  void			*call;

  call = calc_call(opcode, infos, trace->pid, extended);
  upnode = trace->func_stack ? (t_node*)(trace->func_stack->data) : NULL;
  if (call && (node = find_func(call, trace)))
    {
      add_to_list_top(&(trace->func_stack), node);
      if (upnode)
        link_node(upnode, node);
    }
}

int			check_call(t_ftrace *trace)
{
  struct user		infos;
  unsigned short	opcode;
  pid_t		pid;
  int			tmp;

  pid = trace->pid;
  opcode = 0;
  if ((ptrace(PTRACE_GETREGS, pid, NULL, &infos) != -1)
      && (!peek_proc_data(pid, (void*)(infos.regs.rip), (short*)&opcode, 1)))
    {
      if (is_syscall(opcode))
        {
          //print syscall in graph with current syscall
        }
      else if (is_ret_opcode(opcode))
        rm_from_list(&(trace->func_stack), trace->func_stack, NULL);
      else if ((tmp = is_call_opcode(opcode)))
        {
          if (tmp == 2)
            if (!((!peek_proc_data(pid, (void*)(infos.regs.rip + 1),
                                   (short*)&opcode, 1))
                  && is_call_opcode(opcode)))
              return (0);
          call_instruction(trace, &infos, opcode, (tmp == 2));
        }
    }
  return (0);
}

int	check_status(pid_t pid)
{
  int	status;

  if (waitpid(pid, &status, WUNTRACED) == -1)
    return (1);
  if (WIFEXITED(status))
    {
      return (1);
    }
  return (0);
}

void	trace_pid(t_ftrace *trace)
{
  pid_t	pid;
  t_elf	*elf;

  elf = &(trace->elf);
  pid = trace->pid;
  trace->systable = IS_32(1, 0) ? g_syscall_x86_x64 : g_syscall_x86;
  trace->sizetable = (IS_32(1, 0) ? sizeof(g_syscall_x86_x64)
                      : sizeof(g_syscall_x86)) / sizeof(t_syscall_info);
  while (!(check_status(pid)) && !(trace->quit))
    {
      if (!check_call(trace))
        if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
          perror("ptrace");
    }
  if (!trace->forked)
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
}
