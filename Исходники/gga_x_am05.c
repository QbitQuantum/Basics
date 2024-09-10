#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"

#define XC_GGA_X_AM05         120 /* Armiento & Mattsson 05 exchange                */

static inline void 
func(const XC(func_type) *p, int order, FLOAT x, 
     FLOAT *f, FLOAT *dfdx, FLOAT *d2fdx2)
{
  const FLOAT am05_c      = 0.7168;
  const FLOAT am05_alpha  = 2.804;

  const FLOAT z_tt_factor = POW(CBRT(4.0/3.0) * 2.0*M_PI/3.0, 4);

  FLOAT ss, ss2, lam_x, dlam_x, d2lam_x;
  FLOAT ww, z_t, z_t2, z_tt, fx_b, xx, flaa_1, flaa_2, flaa;
  FLOAT dww, dz_t, dz_tt, dfx_b, dxx, dflaa_1, dflaa_2, dflaa;
  FLOAT d2ww, d2z_t, d2z_tt, d2fx_b, d2xx, d2flaa_1, d2flaa_2, d2flaa;;

  if(x < p->info->min_grad){
    *f    = 1.0;
    return;
  }

  ss  = X2S*x;
  ss2 = ss*ss;

  lam_x  = POW(ss, 1.5)/(2.0*SQRT(6.0));