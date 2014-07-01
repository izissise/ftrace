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

uint64_t	three_bit_register(struct user *infos, uint8_t tbit)
{
  uint64_t	regs[16];
  int		extended;

  extended = tbit >> 3;
  regs[0] = infos->regs.rax;
  regs[1] = infos->regs.rcx;
  regs[2] = infos->regs.rdx;
  regs[3] = infos->regs.rbx;
  regs[4] = infos->regs.rsp;
  regs[5] = infos->regs.rbp;
  regs[6] = infos->regs.rsi;
  regs[7] = infos->regs.rdi;
  regs[8] = infos->regs.r8;
  regs[9] = infos->regs.r9;
  regs[10] = infos->regs.r10;
  regs[11] = infos->regs.r11;
  regs[12] = infos->regs.r12;
  regs[13] = infos->regs.r13;
  regs[14] = infos->regs.r14;
  regs[15] = infos->regs.r15;
  if (tbit + (unsigned int)extended * 8 >= (sizeof(regs) / sizeof(uint64_t)))
    return (0);
  return (regs[tbit + extended * 8]);
}
