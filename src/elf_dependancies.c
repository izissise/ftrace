/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#include "symbols.h"
#include "ftrace.h"

void			parse_lib_maps(t_ftrace *trace)
{
  char			mapsfile[BUFSIZ];
  int			fd;
  char			*line;
  int64_t			start;
  int64_t			end;
  long long unsigned int	pop;
  unsigned int			jkl;
  uint64_t		tmp;
  int			posname;
  char			*name;
  char			perm;

  snprintf(mapsfile, sizeof(mapsfile), "/proc/%d/maps", trace->pid);
  if ((fd = open(mapsfile, O_RDONLY)) == -1)
    return ;
  while ((line = get_next_line(fd)))
    {
      sscanf(line, "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu %n",
             &start, &end, &perm, &perm, &perm, &perm,
             &pop, &jkl, &jkl, &tmp, &posname);
      name = &line[posname];
      if (name[0] == '/')
        load_elf(name, trace, start);
      free(line);
    }
}

void	load_libs_symbols(t_ftrace *trace)
{
  parse_lib_maps(trace);
}
