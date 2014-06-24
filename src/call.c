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

int	is_call_opcode(unsigned short opcode)
{
  if (!((opcode & 0xff00U) ^ 0xe800U)
      || !((opcode & 0xff00U) ^ 0x9a00U))
    return (1);
  if (!((opcode & 0xff00U) ^ 0xff00U))
    {
      if (!(((opcode & 0x00ffU) >> 6) ^ 0x2)
          || !(((opcode & 0x00ffU) >> 6) ^ 0x3))
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

int	is_ret_opcode(unsigned short opcode)
{
  if (!((opcode & 0xff00U) ^ 0xc300U)
      || !((opcode & 0xff00U) ^ 0xc200U)
      || !((opcode & 0xff00U) ^ 0xcb00U)
      || !((opcode & 0xff00U) ^ 0xca00U))
    return (1);
  return (0);
}

void	*calc_call(void *opcode)
{

  return (NULL);
}

