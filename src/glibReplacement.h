/* glibReplacement.h: declarations for if fail macros

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

#ifndef PROJECT_GLIBREPLACEMENT_H
#define PROJECT_GLIBREPLACEMENT_H

#define g_return_val_if_fail(condition, value) if(!(condition)) return value

#define g_return_if_fail(condition) if(!(condition)) return

#endif //PROJECT_GLIBREPLACEMENT_H
