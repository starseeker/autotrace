/* xstd.h: Wrappers for functions in C standard library
 Was: xmem, xfile */

/* These call the corresponding function in the standard library, and
   abort if those routines fail. */

#ifndef XSTD_H
#define XSTD_H

#include "types.h"
#include <assert.h>
#include <stdlib.h>

/*
 * XMEM
 */
#ifndef __cplusplus
#define XMALLOC(new_mem, size)			\
do						\
  {						\
    new_mem = (void *) malloc (size);  \
    assert(new_mem);				\
  } while (0)

#define XCALLOC(new_mem, size)			\
do						\
  {						\
    new_mem = (void *) calloc (size, 1);  \
    assert(new_mem);				\
  } while (0)

#define XREALLOC(old_ptr, size)				\
do							\
  {							\
    void * new_mem;          \
							\
    if (old_ptr == NULL)				\
      XMALLOC (new_mem, size);				\
    else						\
      {							\
        new_mem = (void *) realloc (old_ptr, size);  \
        assert(new_mem);				\
      }							\
							\
    old_ptr = new_mem;					\
} while (0)

#else
/* Use templates if Cplusplus... */
#define XMALLOC(new_mem, size)					\
do								\
  {								\
    (void *&)(new_mem) = (void *) malloc (size);	\
     assert(new_mem);						\
  } while (0)

#define XCALLOC(new_mem, sizex)					\
do								\
  {								\
    (void *&)(new_mem) = (void *) calloc (sizex, 1);	\
    assert(new_mem);						\
  } while (0)

#define XREALLOC(old_ptr, size)						  \
do									  \
  {									  \
    void * new_mem;							  \
									  \
    if (old_ptr == NULL)						  \
      XMALLOC (new_mem, (size));					  \
    else								  \
      {									  \
        (void *&) new_mem = (void *) realloc ((old_ptr), (size)); \
        assert(new_mem);						  \
      }									  \
									  \
    (void *&)old_ptr = new_mem;					  \
  } while (0)
#endif

#endif /* Not XSTD_H */
