/*
** calloc.c for  in /home/melis_m/code/malloc/src
**
** Made by matteo melis
** Login   <melis_m@epitech.net>
**
** Started on  Tue Jan 31 18:25:18 2017 matteo melis
** Last update Tue Jan 31 18:25:18 2017 matteo melis
*/

#include "my_malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  size_t	tsize;
  void		*ptr;

  if (!nmemb || !size)
    return (NULL);
  tsize = nmemb * size;
  ptr = malloc(tsize);
  if (ptr)
    memset(ptr, 0, tsize);
  return (ptr);
}
