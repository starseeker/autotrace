/* filename.h: Function manipulate file names
   Was: find-suffix, extend-fname, make-suffix, remove-suffix  */

/* remove-suffx.h: declarations for shared routines.

Copyright (C) 1992 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef FILENAME_H
#define FILENAME_H
#include "types.h"

/* If NAME has a suffix, return a pointer to its first character (i.e.,
   the one after the `.'); otherwise, return NULL.  */
extern char *find_suffix(char *name);

/* If NAME has a suffix, simply return it; otherwise, return
   `NAME.SUFFIX'.  */
extern char *extend_filename(char *name, char *suffix);

/* Return S with the suffix SUFFIX, removing any suffix already present.
   For example, `make_suffix ("/foo/bar.baz", "karl")' returns
   `/foo/bar.karl'.  Returns a string allocated with malloc.  */
extern char *make_suffix(char *s, char *suffix);

/* Return NAME with any suffix removed.  */
extern char *remove_suffix(char *name);

#endif /* Not def: FILENAME_H */
