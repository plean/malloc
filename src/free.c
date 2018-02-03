/*
** free.c for  in /home/melis_m/code/malloc/bonus/src
**
** Made by matteo melis
** Login   <melis_m@epitech.net>
**
** Started on  Tue Jan 31 18:31:45 2017 matteo melis
** Last update Tue Jan 31 18:31:45 2017 matteo melis
*/

#include <pthread.h>
#include "my_malloc.h"

extern t_block_data	*g_first_block;
extern pthread_mutex_t	g_lock;

void		free(void *ptr)
{
  t_block_data	*data;

  pthread_mutex_lock(&g_lock);
  data = META_DATA(ptr);
  if (ptr)
    {
      data->is_free = TRUE;
      if (data->size + BLOCK_DATA_SIZE > BUDDY_PAGE_SIZE_MAX)
      	{
      	  while (data->next && data->is_free)
      	    data = data->next;
      	  if (data->is_free)
	    {
	      if (data->prev)
		data->prev->next = NULL;
	      else
		g_first_block = NULL;
	      brk(ptr - BLOCK_DATA_SIZE);
	    }
      	}
    }
  pthread_mutex_unlock(&g_lock);
}
