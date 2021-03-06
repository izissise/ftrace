/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

int	my_swap_char(char *a, char *b)
{
  if (a != b )
    {
      *a = *a + *b;
      *b = *a - *b;
      *a = *a - *b;
    }
  return (0);
}

void	*switch_endian(void *var, int varsize)
{
  int	i;
  int	j;

  i = 0;
  while (i < varsize)
    {
      j = 0;
      while (j < i)
        {
          my_swap_char(&((char*)var)[i], &((char*)var)[j]);
          j++;
        }
      i++;
    }
  return (var);
}
