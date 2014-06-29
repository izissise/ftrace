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
** 41 extend for register in x86_x64
*/

inline int	is_call_opcode(unsigned short opcode)
{
  uint8_t	modbyte;

  if (!((opcode & 0x00ffU) ^ 0x00e8U)
      || !((opcode & 0x00ffU) ^ 0x009aU))
    return (1);
  if (opcode == 0xff41)
    return (2);
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
** f2 rep prefix
** f3 rep prefix
*/

inline int	is_ret_opcode(unsigned short opcode)
{
  if (!((opcode & 0x00ffU) ^ 0x00f2U)
      || !((opcode & 0x00ffU) ^ 0x00f3U))
    opcode >>= 8;
  if (!((opcode & 0x00ffU) ^ 0x00c3U)
      || !((opcode & 0x00ffU) ^ 0x00c2U)
      || !((opcode & 0x00ffU) ^ 0x00cbU)
      || !((opcode & 0x00ffU) ^ 0x00caU))
    return (1);
  return (0);
}

static inline void	*call_ff_case(struct user *infos, pid_t pid,
                                  char instr[12], int extended)
{
  unsigned short		opcode;
  uint8_t			modregrmbyte;
  uint8_t			mod;
  uint8_t			reg;
  uint8_t			rm;
  void				*res;
  uint32_t		tmp;

  res = NULL;
  opcode = *((unsigned short*)instr);
  modregrmbyte = ((opcode & 0xff00U) >> 8);
  mod = (modregrmbyte >> 6) & 0x3U;
  reg = (modregrmbyte >> 3) & 0x7U;
  rm = (modregrmbyte) & 0x7U;
  if (mod == 0x3U)
    res = (void*)three_bit_register(infos, rm, extended);
  else
    {
      if (rm == 0x4U)
        {
          printf("oops\n");
        }
      else if (rm == 0x5U)
        {
          printf("oops\n");
        }
      else
        {
          res = (void*)three_bit_register(infos, rm, extended);
          if (peek_proc_data_size(pid, res, (void*)&res, sizeof(void*)))
            return (NULL);
        }
    }
  return (res);
}

void	*calc_call(unsigned short opcode, struct user *infos,
                 pid_t pid, int extended)
{
  char	instr[12];
  void	*res;

  res = NULL;
  if (peek_proc_data_size(pid, (void*)(infos->regs.rip + extended),
                          instr, sizeof(instr)))
    return (NULL);
  if (!((opcode & 0x00ffU) ^ 0x00e8U))
    res = (void*)((void*)(infos->regs.rip) + (*((int32_t*)(&instr[1]))) + 5);
  else if (!((opcode & 0x00ffU) ^ 0x00ffU))
    res = call_ff_case(infos, pid, instr, extended);
  else if (!((opcode & 0x00ffU) ^ 0x009aU))
    res = (void*)((uint64_t)(*((int32_t*)(&instr[1]))) + 7);
  return (res);
}

