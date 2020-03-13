/* input-magick.c: import files via image magick

   Copyright (C) 1999, 2000, 2001 Martin Weber.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* Needed for correct interpretation of magick/api.h */
#define MagickLibVersion 0x0626  /* workaround because not yet defined */
#if (MagickLibVersion < 0x0626)
#undef MagickLibVersion
#include <magick/api.h>
#else
#undef MagickLibVersion
#include <MagickCore/magickCore.h>
#endif
#include "input-magick.h"
#include "bitmap.h"
#include "input.h"

static at_bitmap input_magick_reader(char * filename, at_input_opts_type * opts, at_msg_func msg_func, void * msg_data, void * user_data)
{
  Image *image = NULL;
  ImageInfo *image_info;
  ImageType image_type;
  unsigned int i,j,point,np,runcount;
  at_bitmap_type bitmap;
#if (MagickLibVersion < 0x0645)
  PixelPacket p;
  PixelPacket *pixel=&p;
#else
  Quantum quantum[32]; /* no idea why it must be this number, otherwise memory of other variables becomes corrupted */
#endif
  ExceptionInfo exception;
#if (MagickLibVersion < 0x0538)
  MagickIncarnate("");
#elif (MagickLibVersion < 0x0634)
  InitializeMagick("");
#else
  MagickCoreGenesis("", MagickTrue);
#endif
#if (MagickLibVersion < 0x0626)
  GetExceptionInfo(&exception);
#else
  exception = *AcquireExceptionInfo();
#endif

#if (MagickLibVersion < 0x0629)
  image_info=CloneImageInfo((ImageInfo *) NULL);
#else
  image_info = AcquireImageInfo();
#endif

  (void) strcpy(image_info->filename,filename);
  image_info->antialias = 0;

  image=ReadImage(image_info,&exception);
  if (image == (Image *) NULL) {
#if (MagickLibVersion <= 0x0525)
    /* MagickError(exception.severity,exception.message,exception.qualifier); */
    if (msg_func)
      msg_func (exception.qualifier, AT_MSG_FATAL, msg_data);
    goto cleanup;
#else
    /* MagickError(exception.severity,exception.reason,exception.description); */
    if (msg_func)
      msg_func (exception.reason, AT_MSG_FATAL, msg_data);
    goto cleanup;
#endif
  }
#if (MagickLibVersion < 0x0540 || MagickLibVersion > 0x0697)
  image_type=GetImageType(image);
#else
  image_type = GetImageType(image, &exception);
#endif
  if(image_type == BilevelType || image_type == GrayscaleType)
    np=1;
  else
    np=3;

  bitmap = at_bitmap_init(NULL, image->columns, image->rows, np);

  for(j=0,runcount=0,point=0;j<image->rows;j++)
    for(i=0;i<image->columns;i++) {
#if (MagickLibVersion < 0x0645)
		p = GetOnePixel(image, i, j);
		AT_BITMAP_BITS(bitmap)[point++] = pixel->red; /* if gray: red=green=blue */
		if (np == 3) {
			AT_BITMAP_BITS(bitmap)[point++] = pixel->green;
			AT_BITMAP_BITS(bitmap)[point++] = pixel->blue;
	    }
#else
		if (GetOneVirtualPixel(image, i, j, quantum, &exception) == false) {
			if (msg_func)
				msg_func(exception.reason, AT_MSG_FATAL, msg_data);
			goto cleanup;
		}
		AT_BITMAP_BITS(bitmap)[point++] = ScaleQuantumToChar(quantum[0]); /* if gray: red=green=blue */
		if (np == 3) {
			AT_BITMAP_BITS(bitmap)[point++] = ScaleQuantumToChar(quantum[1]);
			AT_BITMAP_BITS(bitmap)[point++] = ScaleQuantumToChar(quantum[2]);
		}
#endif
    }

  DestroyImage(image);
 cleanup:
  DestroyImageInfo(image_info);  
  return(bitmap);
}

int install_input_magick_readers(void)
{
  ExceptionInfo exception;
  MagickInfo *info, *magickinfo;
  InitializeMagick("");

  GetExceptionInfo(&exception);

  info = GetMagickInfo(NULL, &exception);
  if (info && !info->next)
    info = GetMagickInfo("*", &exception);
  magickinfo = info;

  while (info) {
    if (info->name && info->description)
      at_input_add_handler_full(info->name, info->description, input_magick_reader, 0, info->name, NULL);
    info = info->next;
  }
  return 0;
}
