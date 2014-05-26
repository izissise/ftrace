/*
** main.c for  in /home/fritsc_h/AUSP_strace/src
**
** Made by Harold Fritsch
** Login   <fritsc_h@epitech.net>
**
** Started on  Thu May  1 18:27:53 2014 Harold Fritsch
** Last update Fri May  2 16:54:41 2014 Harold Fritsch
*/

#ifndef TYPE_MAP_H_INCLUDED
# define TYPE_MAP_H_INCLUDED

# include "strace.h"

t_type_map	g_typemap[] = {
  {"int", &trace_int},
  {"key_t", &trace_int},
  {"pid_t", &trace_int},
  {"ssize_t", &trace_int},
  {"off_t", &trace_int},
  {"long int", &trace_int},
  {"long", &trace_int},
  {"unsigned int", &trace_uint},
  {"unsigned long", &trace_uint},
  {"size_t", &trace_uint},
  {"uid_t", &trace_uint},
  {"gid_t", &trace_uint},
  {"mode_t", &trace_uint},
  {"dev_t", &trace_uint},
  {"char*", &trace_chartoile},
  {"char**", &trace_chartoiletoile},
  {"void*", &trace_ptrtoile},
  {"void", &trace_void},
  {"struct stat*", &trace_ststat},
  {"struct statfs*", &trace_ptrtoile}
};

#endif /* !TYPE_MAP_H_INCLUDED */
