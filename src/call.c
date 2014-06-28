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

/*
** e8 Xx call
** 9a Xx call
** ff /2 Xx call
** ff /3 Xx call
*/

inline int	is_call_opcode(unsigned short opcode)
{
  uint8_t	modbyte;

  if (!((opcode & 0x00ffU) ^ 0x00e8U)
      || !((opcode & 0x00ffU) ^ 0x009aU))
    return (1);
  if (!((opcode & 0x00ffU) ^ 0x00ffU))
    {
      modbyte = ((opcode & 0xff00U) >> 8);
      if (!(((modbyte >> 3) & 0x7U) ^ 0x2U)
          || !(((modbyte >> 3) & 0x7U) ^ 0x3U))
        return (1);
    }
  return (0);
}

/*
** c3 xx ret       (cdecl)
** c2 xx xx ret X  (stdcall)
** cb xx ret (far call)
** ca ** ** ret X (far call)
*/

inline int	is_ret_opcode(unsigned short opcode)
{
  if (!((opcode & 0x00ffU) ^ 0x00c3U)
      || !((opcode & 0x00ffU) ^ 0x00c2U)
      || !((opcode & 0x00ffU) ^ 0x00cbU)
      || !((opcode & 0x00ffU) ^ 0x00caU))
    return (1);
  return (0);
}

void	*calc_call(unsigned short opcode, struct user *infos, pid_t pid)
{
  char	instr[10];
  void	*res;
  uint8_t	modbyte;

  res = NULL;
  if (peek_proc_data_size(pid, (void*)(infos->regs.rip), instr, sizeof(instr)))
    return (NULL);
  if (!((opcode & 0x00ffU) ^ 0x00e8U))
    res = (void*)((void*)(infos->regs.rip) + (*((int32_t*)(&instr[1]))) + 5);
  else if (!((opcode & 0x00ffU) ^ 0x00ffU))
    {
      modbyte = ((opcode & 0xff00U) >> 8);
      res = (void*)three_bit_register(infos, modbyte & 0x7U, 0);
    }
  else if (!((opcode & 0x00ffU) ^ 0x009aU))
    res = (void*)((uint64_t)(*((int32_t*)(&instr[1]))) + 7);
  return (res);
}
