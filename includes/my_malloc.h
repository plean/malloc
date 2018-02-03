#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

/*
** Includes
*/

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

/*
** Usefull define
*/

# define FALSE (0)
# define TRUE (1)

/*
** Arithmetic trics
*/

# define ALIGN4(x) (((((x) - 1) >> 2) << 2) + 4)
# define ALIGN8(x) (((((x) - 1) >> 3) << 3) + 8)
# define ALIGN16(x) (((((x) - 1) >> 4) << 4) + 16)

/*
** Bits table
*/

# define B * 1
# define KB * 1024 B
# define MB * 1024 KB
# define GB * 1024 MB

/*
** Octets table
*/

# define O * 8 B
# define KO * 8 KB
# define MO * 8 MB
# define GO * 8 GB

/*
** Buddy page size
*/

# define BUDDY_PAGE_SIZE_MAX (4 KO)
# define BUDDY_PAGE_SIZE_MIN (4 O)

/*
** BlockData information
*/

typedef struct		s_block_data
{
  size_t		size;
  int			is_free;
  struct  s_block_data	*next;
  struct  s_block_data	*prev;
}			t_block_data;

# define BLOCK_DATA_SIZE (sizeof(struct s_block_data))
# define META_DATA(x) (x - BLOCK_DATA_SIZE)

/*
** Prototypes
*/

void	*malloc(size_t size);
void	*calloc(size_t nmemb, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem(void);

#endif /* !MY_MALLOC_H_ */
