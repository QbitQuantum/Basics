#define XC_GGA_X_PBEA  121 /* Madsen (PBE-like) */

/* PBEA: see PBE for more details */
static inline void 
func(const XC(func_type) *p, int order, FLOAT x, 
     FLOAT *f, FLOAT *dfdx, FLOAT *d2fdx2)
{
  static const FLOAT kappa = 0.8040;
  static const FLOAT mu = 0.00361218645365094697;
  /* hard-coded alpha*/
  static const FLOAT alpha = 0.5;

  FLOAT f0, df0, d2f0;

  f0 = 1.0 + mu*x*x/(alpha*kappa);
  *f = 1.0 + kappa*(1.0 - POW(f0, -alpha));

  if(order < 1) return;

  df0 = 2.0*mu*x/(alpha*kappa);

  *dfdx  = alpha*kappa*df0*POW(f0, -(alpha + 1.0));

  if(order < 2) return;

  d2f0 = 2.0*mu/(alpha*kappa);
  *d2fdx2 = alpha*kappa*POW(f0, -alpha - 1.0)*
    (d2f0 - (alpha + 1.0)*df0*df0/f0);
}

#include "work_gga_x.c"