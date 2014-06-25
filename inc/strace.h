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

typedef struct	s_ftrace t_ftrace;

typedef struct	s_syscall_info
{
  char		*name;
  char		*ret;
  char		*args[9];
}		t_syscall_info;

inline int	is_syscall(unsigned short opcode);

#endif /* !STRACE_H_INCLUDED */
