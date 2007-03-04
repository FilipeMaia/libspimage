#ifndef _CIMAGE_H_
#define _CIMAGE_H_

#include <float.h>
#include <complex.h>

#ifdef DOUBLE
typedef double real;
typedef _Complex double Complex;
#define REAL_MAX DBL_MAX
#define REAL_EPSILON DBL_EPSILON
#define conjr(a) conj(a)
#define cabsr(a) cabs(a)
#define cargr(a) carg(a)
#else
typedef float real;
typedef _Complex float Complex;
#define REAL_MAX FLT_MAX
#define REAL_EPSILON FLT_EPSILON
#define cabsr(a) cabsf(a)
#define conjr(a) conjf(a)
#define cargr(a) cargf(a)
#endif


#if defined(_WIN32) || defined(WIN32) /* Win32 version */
#ifdef spimage_EXPORTS
#  define spimage_EXPORT __declspec(dllexport)
#else
#  define spimage_EXPORT __declspec(dllimport)
#endif
#else
/* unix needs nothing */
#define spimage_EXPORT
#endif

#include "linear_alg.h"

/*! Structure that keeps all the information about the Detector type.

*/

typedef struct{
  real image_center[2];
  real pixel_size;
  real detector_distance;
  real lambda;
}Detector;


/*! Main structure that keeps all the information about an image.

*/


typedef struct{
  /* this flag tell us whether we should try to access
   the real and complex part of the image seperately or
   just the amplitudes */
  int phased;  
  /* this flag tell us whether we should try to access
   the amplitudes (when scaled) or the intensities
  (when unscalled) */
  int scaled;
  /* The actual image */
  sp_cmatrix * image;
  /* The integer mask */
  sp_imatrix * mask;
  Detector * detector;
  /* this flag tells wether the image is shifted 
     (in FFTW format, center on the corners) or not*/
  int shifted;
}Image;

#endif
