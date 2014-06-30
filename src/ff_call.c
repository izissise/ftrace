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

inline static void	*deref_reg(struct user *infos, pid_t pid,
                               uint8_t rm, int extended)
{
  void			*res;
  uint64_t		tmp;

  res = (void*)three_bit_register(infos, rm, extended);
  if (peek_proc_data_size(pid, res, (void*)&tmp, sizeof(tmp)))
    return (NULL);
  printf("deref: %p\n", (void*)(uint64_t)tmp);
  return ((void*)(uint64_t)tmp);
}

inline static void	*displacement_value(char instr[12], int *instr_size,
                                        uint8_t mod)
{
  void			*res;

  res = NULL;
  if (mod == 0x1U)
    {
      res = (void*)((int64_t)(*((int8_t*)(&instr[*instr_size]))));
      *instr_size += 1;
    }
  else if (mod == 0x2U)
    {
      res = (void*)((int64_t)(*((int32_t*)(&instr[*instr_size]))));
      *instr_size += 4;
    }
  if (res)
    printf("Displacemnet !!!\n");
  return (res);
}

inline void		*call_ff_case(struct user *infos, pid_t pid,
                            char instr[12], int extended)
{
  uint8_t			mod;
  uint8_t			reg;
  uint8_t			rm;
  void				*res;
  int			instr_size;

  res = NULL;
  instr_size = 2;
  mod = ((((*((unsigned short*)instr)) & 0xff00U) >> 8) >> 6) & 0x3U;
  reg = ((((*((unsigned short*)instr)) & 0xff00U) >> 8) >> 3) & 0x7U;
  rm = ((((*((unsigned short*)instr)) & 0xff00U) >> 8)) & 0x7U;
  if (reg == 0x3U)
    printf("This is Madness !!\n");
  if (mod == 0x3U)
    res = (void*)three_bit_register(infos, rm, extended);
  else
    {
      if (rm == 0x4U)
        {
          //sib byte
          printf("oops\n");
          instr_size += 1;
        }
      else if (rm == 0x5U)
        {
          // direct value
          printf("oops\n");
          instr_size += 1;
        }
      else
        res = deref_reg(infos, pid, rm, extended);
      res = (void*)((int64_t)res
                    + (int64_t)displacement_value(instr, &instr_size, mod));
    }
  return (res);
}

