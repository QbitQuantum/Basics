#include "util.h"

#define XC_GGA_X_2D_B86_MGC      124 /* Becke 86 MGC for 2D systems */

static inline void
func(const XC(func_type) *p, int order, FLOAT x, 
     FLOAT *f, FLOAT *dfdx, FLOAT *d2fdx2)
{
  static const FLOAT beta=0.003317, gam=0.008323;

  FLOAT dd, ddp, f1, f2, df1, df2, d2f1, d2f2;

  dd    = 1.0 + gam*x*x;

  f1    = beta/X_FACTOR_C*x*x;
  f2    = POW(dd, 3.0/4.0);
  *f    = 1.0 + f1/f2;

  if(order < 1) return; /* nothing else to do */

  df1 = beta/X_FACTOR_C*2.0*x;
  ddp = gam*2.0*3.0/4.0*f2/dd;
  df2 = ddp*x;

  *dfdx  = (df1*f2 - f1*df2)/(f2*f2);

  if(order < 2) return; /* nothing else to do */

  d2f1 = beta/X_FACTOR_C*2.0;
  d2f2 = ddp*(1.0 - 2.0/4.0*gam*x*x/dd);
