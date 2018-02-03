/*
** malloc.c for  in /home/melis_m/code/malloc/bonus/src
** 
** Made by matteo melis
** Login   <melis_m@epitech.net>
** 
** Started on  Tue Jan 31 18:32:26 2017 matteo melis
** Last update Tue Jan 31 18:32:26 2017 matteo melis
*/

#include <pthread.h>
#include "my_malloc.h"

t_block_data	*g_first_block = NULL;
pthread_mutex_t	g_lock;

static void	split_existing_block(t_block_data *existing_block, size_t size)
{
  t_block_data	*new_block;
  size_t	new_size;

  new_size = size - BLOCK_DATA_SIZE;
  new_block = (void *)existing_block + size;
  new_block->is_free = TRUE;
  new_block->size = new_size;
  existing_block->size = new_size;
  new_block->prev = existing_block;
  new_block->next = existing_block->next;
  existing_block->next = new_block;
}

static void	*create_new_block_s(t_block_data *data, size_t size)
{
  t_block_data	*tmp;

  size += BLOCK_DATA_SIZE;
  size--;
  size |= size >> 1;
  size |= size >> 2;
  size |= size >> 4;
  size |= size >> 8;
  size |= size >> 16;
  size++;
  if (sbrk(size) == (void *)-1)
    return (NULL);
  data->size = size - BLOCK_DATA_SIZE;
  tmp = g_first_block;
  data->next = NULL;
  data->prev = NULL;
  while (tmp->next)
    tmp = tmp->next;
  if (tmp != data)
    {
      tmp->next = data;
      data->prev = tmp;
    }
  data->is_free = FALSE;
  return (data);
}

static void	*create_new_block(size_t size)
{
  t_block_data	*data;
  t_block_data	*tmp;

  data = sbrk(0);
  if (size + BLOCK_DATA_SIZE > BUDDY_PAGE_SIZE_MAX)
    return create_new_block_s(data, size);
  else if (sbrk(BUDDY_PAGE_SIZE_MAX) == (void *)-1)
    return (NULL);
  data->size = BUDDY_PAGE_SIZE_MAX - BLOCK_DATA_SIZE;
  tmp = g_first_block;
  data->next = NULL;
  data->prev = NULL;
  while (tmp->next)
    tmp = tmp->next;
  if (tmp != data)
    {
      tmp->next = data;
      data->prev = tmp;
    }
  while ((data->size + BLOCK_DATA_SIZE) >> 1 >= size + BLOCK_DATA_SIZE)
    split_existing_block(data, (data->size + BLOCK_DATA_SIZE) >> 1);
  data->is_free = FALSE;
  return (data);
}

void		*malloc(size_t size)
{
  t_block_data	*data;

  if (size > SIZE_MAX - BLOCK_DATA_SIZE)
    return (NULL);
  if (!g_first_block)
    pthread_mutex_init(&g_lock, NULL);
  pthread_mutex_lock(&g_lock);
  if ((data = g_first_block))
    while (data)
      {
	if (data->is_free == TRUE && data->size >= size)
	  {
	    while ((data->size + BLOCK_DATA_SIZE) >> 1 >= size + BLOCK_DATA_SIZE)
	      split_existing_block(data, (data->size + BLOCK_DATA_SIZE) >> 1);
	    data->is_free = FALSE;
	    pthread_mutex_unlock(&g_lock);
	    return (data + 1);
	  }
	data = data->next;
      }
  else
    g_first_block = sbrk(0);
  data = create_new_block(size);
  pthread_mutex_unlock(&g_lock);
  return (data ? data + 1 : NULL);
}
