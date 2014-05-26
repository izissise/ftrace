/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#ifndef SPECIAL_SYSCALLPARAM_H_INCLUDED
# define SPECIAL_SYSCALLPARAM_H_INCLUDED

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

t_special_print	g_special_print[] = {
  { "open", 1, {
      {O_RDWR, "O_RDWR"},
      {O_RDONLY, "O_RDONLY"},
      {O_WRONLY, "O_WRONLY"},
      {O_APPEND, "O_APPEND"},
      {O_ASYNC, "O_ASYNC"},
      {O_CLOEXEC, "O_CLOEXEC"},
      {O_CREAT, "O_CREAT"},
      {O_DIRECTORY, "O_DIRECTORY"},
      {O_EXCL, "O_EXCL"},
      {O_NOCTTY, "O_NOCTTY"},
      {O_NOFOLLOW, "O_NOFOLLOW"},
      {O_NONBLOCK, "O_NONBLOCK"},
      {O_SYNC, "O_SYNC"},
      {O_TRUNC, "O_TRUNC"},
      {0, NULL}
    }
  },
  { "access", 1, {
      {F_OK, "F_OK"},
      {R_OK, "R_OK"},
      {W_OK, "W_OK"},
      {X_OK, "X_OK"},
      {0, NULL}
    }
  },
  { "mmap", 2, {
      {PROT_NONE, "PROT_NONE"},
      {PROT_EXEC, "PROT_EXEC"},
      {PROT_READ, "PROT_READ"},
      {PROT_WRITE, "PROT_WRITE"},
      {0, NULL}
    }
  },
  { "mmap", 3, {
      {MAP_SHARED, "MAP_SHARED"},
      {MAP_PRIVATE, "MAP_PRIVATE"},
      {MAP_32BIT, "MAP_32BIT"},
      {MAP_ANONYMOUS, "MAP_ANONYMOUS"},
      {MAP_DENYWRITE, "MAP_DENYWRITE"},
      {MAP_FIXED, "MAP_FIXED"},
      {MAP_GROWSDOWN, "MAP_GROWSDOWN"},
      {MAP_HUGETLB, "MAP_HUGETLB"},
      {MAP_LOCKED, "MAP_LOCKED"},
      {MAP_NONBLOCK, "MAP_NONBLOCK"},
      {MAP_NORESERVE, "MAP_NORESERVE"},
      {MAP_POPULATE, "MAP_POPULATE"},
      {MAP_STACK, "MAP_STACK"},
      {0, NULL}
    }
  }
};

#endif /* !SPECIAL_SYSCALLPARAM_H_INCLUDED */
