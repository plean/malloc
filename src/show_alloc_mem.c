/*
** show_alloc_mem.c for  in /home/melis_m/code/malloc/src
**
** Made by matteo melis
** Login   <melis_m@epitech.net>
**
** Started on  Tue Jan 31 18:26:46 2017 matteo melis
** Last update Tue Jan 31 18:26:46 2017 matteo melis
*/

#include "my_malloc.h"

extern t_block_data	*g_first_block;

static void	putnbr(char *str, size_t nb)
{
  (nb / strlen(str) == 0) ? (1) :
    putnbr(str, nb / strlen(str));
  write(1, str + (nb % strlen(str)), 1);
}

static void	putstr(char *str)
{
  write(1, str, strlen(str));
}

void		show_alloc_mem(void)
{
  t_block_data	*data;

  data = g_first_block;
  putstr("break : 0x");
  putnbr("0123456789ABCDEF", (size_t)sbrk(0));
  putstr("\n");
  putstr("start of heap : 0x");
  putnbr("0123456789ABCDEF", (size_t)g_first_block);
  putstr("\n");
  while (data)
    {
      if (data->is_free == FALSE)
	{
          putstr("0x");
          putnbr("0123456789ABCDEF", (size_t)(data + 1));
          putstr(" - 0x");
          putnbr("0123456789ABCDEF", (size_t)((void *)(data + 1) + data->size));
          putstr(" : ");
          putnbr("0123456789", data->size);
          putstr(" bytes\n");
	}
      data = data->next;
    }
}
