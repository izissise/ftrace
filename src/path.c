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
#include <unistd.h>

#include "ftrace.h"

int			check_if_folder(char *file)
{
  struct stat	s;

  if (stat(file, &s) == -1)
    return (-1);
  else if ((s.st_mode & 0170000) == 0040000)
    return (1);
  return (0);
}

/*
** Return the full path of a command , return the command if didn't find it
** for trying to execute it from the current directory
*/

char	*exec_full_path(char *exec, char **paths)
{
  char	*fpaths;
  int	len;

  fpaths = NULL;
  while ((exec != NULL) && (paths != NULL) && (paths[0] != NULL))
    {
      len = (exec ? strlen(exec) : 0) + (paths[0] ? strlen(paths[0]) : 0) + 2;
      if ((fpaths = malloc(sizeof(char) * len)) == NULL)
        return (exec ? strdup(exec) : NULL);
      snprintf(fpaths, len, "%s/%s", paths[0], exec);
      if ((access(fpaths, F_OK) == 0) && (access(fpaths, X_OK) == 0)
          && (check_if_folder(fpaths) == 0))
        return (fpaths);
      free(fpaths);
      paths = &paths[1];
    }
  return (exec ? strdup(exec) : NULL);
}

char	**path_to_tab(char *path)
{
  char	**res;
  char	**tmpptr;
  int	nbpaths;
  char	*tmp;

  if (!path)
    return (NULL);
  res = NULL;
  nbpaths = 1;
  if (((tmp = strtok(path, ":")))
      && ((res = realloc(res, (nbpaths + 1) * sizeof(char*)))))
    res[nbpaths - 1] = tmp;
  while (tmp != NULL)
    {
      nbpaths++;
      tmp = strtok(NULL, ":");
      if ((tmpptr = realloc(res, (nbpaths + 1) * sizeof(char*))))
        {
          res = tmpptr;
          res[nbpaths - 1] = tmp;
        }
    }
  if (res)
    res[nbpaths] = NULL;
  return (res);
}

char	*prog_full_path(char *prog)
{
  char	*path_env;
  char	*tmp;
  char	**path;
  char	*res;

  path_env = getenv("PATH");
  if (!path_env)
    return (NULL);
  tmp = strdup(path_env);
  path = path_to_tab(tmp);
  res = exec_full_path(prog, path);
  free(tmp);
  free(path);
  if ((access(res, F_OK) == 0) && (access(res, X_OK) == 0)
      && (check_if_folder(res) == 0))
    return (res);
  free(res);
  return (NULL);
}
