/* fit.h: convert the pixel representation to splines. */

#ifndef FIT_H
#define FIT_H

#include "autotrace.h"
#include "image-proc.h"
#include "pxl-outline.h"
#include "spline.h"
#include "exception.h"


#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/* See fit.c for descriptions of these variables, all of which can be
   set using options.  */
typedef at_fitting_opts_type fitting_opts_type;

/* Fit splines and lines to LIST.  */
extern spline_list_array_type
fitted_splines(pixel_outline_list_type, fitting_opts_type *, at_distance_map *, unsigned short width,
               unsigned short height, at_exception_type *exception, at_progress_func, void *, at_testcancel_func,
               void *);

/* Get a new set of fitting options */
fitting_opts_type new_fitting_opts(void);


#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#endif /* not FIT_H */
