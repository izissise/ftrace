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
                               uint8_t rm, void *displacement)
{
  void			*res;
  uint64_t		tmp;

  res = (void*)three_bit_register(infos, rm) + (int64_t)displacement;
  if (peek_proc_data_size(pid, res, (void*)&tmp, sizeof(tmp)))
    return (NULL);
  return ((void*)(uint64_t)tmp);
}

inline static void	*displacement_value(char instr[15], int *instr_size,
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
  printf("displacement! %p\n", res);
  return (res);
}

inline void		*sib_byte(struct user *infos, pid_t pid,
                        char instr[15], unsigned short extended)
{
  (void)infos;
  (void)pid;
  (void)instr;
  (void)extended;
  return (NULL);
}

inline void		*call_ff_case(struct user *infos, pid_t pid,
                            char instr[15], unsigned short extended)
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
    res = (void*)three_bit_register(infos, rm + ((extended ? 1 : 0) << 3));
  else
    {
      instr_size += ((rm == 0x4U) ? 1 : 0);
      res = (void*)((int64_t)displacement_value(instr, &instr_size, mod));
      if ((rm == 0x4U) && ((uint8_t)instr[2] != 0x24U))
        res = sib_byte(infos, pid, instr, extended);
      else if (!((rm == 0x5U) && (mod == 0x0U)))
        res = deref_reg(infos, pid, rm + ((extended ? 1 : 0) << 3), res);
    }
  return (res);
}
