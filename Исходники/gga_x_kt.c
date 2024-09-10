#include "util.h"

#define XC_GGA_X_KT1          145 /* Keal and Tozer version 1             */
#define XC_GGA_XC_KT2         146 /* Keal and Tozer version 2             */

#define HEADER 3

static inline void 
func(const XC(gga_type) *p, int order, FLOAT x, FLOAT ds,
     FLOAT *f, FLOAT *dfdx, FLOAT *lvrho)
{
  FLOAT gamma = -0.006, delta = 0.1;

  FLOAT dd, n13, n43;

  n13 = CBRT(ds);
  n43 = ds*n13;
  dd  = 1.0/(n43 + delta);
 
  *f = 1.0 - gamma/X_FACTOR_C * x*x * n43*dd;

  if(order < 1) return;

  *dfdx  = - gamma/X_FACTOR_C * 2.0*x * n43*dd;
  *lvrho = - gamma/X_FACTOR_C * x*x * (4.0/3.0)*n13 * delta * dd*dd;

  if(order < 2) return;

  /* to be done */
}
