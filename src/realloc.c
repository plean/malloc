/*
** realloc.c for  in /home/melis_m/code/malloc/src
** 
** Made by matteo melis
** Login   <melis_m@epitech.net>
** 
** Started on  Tue Jan 31 18:26:43 2017 matteo melis
** Last update Tue Jan 31 18:26:43 2017 matteo melis
*/

#include "my_malloc.h"

void		*realloc(void *ptr, size_t size)
{
  t_block_data	*data;
  void		*tmp;

  if (!ptr)
    return (malloc(size));
  data = META_DATA(ptr);
  if (data->size >= size)
    return (ptr);
  if (!size)
    {
      free(ptr);
      return (NULL);
    }
  tmp = malloc(size);
  memmove(tmp, data + 1, data->size);
  free(ptr);
  return (tmp);
}
