/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "strace.h"

int	is_64_bit(int fd)
{
  char	path[512];
  int	tmp;

  if (fd == -1)
    return (2);
  tmp = read(fd, path, 10);
  close(fd);
  if (tmp < 6)
    return (3);
  if (path[4] == 1)
    return (0);
  return (1);
}

int	is_64_bit_pid(pid_t pid)
{
  int	fd;
  char	path[512];

  snprintf(path, sizeof(path), "/proc/%lu/exe", (long int)pid);
  fd = open(path, O_RDONLY);
  return (is_64_bit(fd));
}

int	is_64_bit_path(const char *path)
{
  int	fd;

  fd = open(path, O_RDONLY);
  return (is_64_bit(fd));
}
