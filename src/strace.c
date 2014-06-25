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

/*
** 0f 05 syscall
** 0f 34 sysenter
** cd 80 int 0x80
*/

inline int	is_syscall(unsigned short opcode)
{
  if (!(opcode ^ 0x050fU)
      || !(opcode ^ 0x340fU)
      || !(opcode ^ 0x80cdU))
    return (1);
  return (0);
}

