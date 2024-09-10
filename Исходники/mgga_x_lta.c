#include <assert.h>
#include "util.h"

/* Local tau approximation */

#define XC_MGGA_X_LTA          201 /* Local tau approximation of Ernzerhof & Scuseria */

static void 
func(const XC(func_type) *pt, XC(mgga_work_x_t) *r)
{
  /* POW(10.0/(3.0*POW(6.0*M_PI*M_PI, 2.0/3.0)), 4.0/5.0) = (2/C_F)^(4/5) */
  const FLOAT a1 = 0.297163728291293581339216378935;
  FLOAT t;

  t  = r->t; /* we use a different definition of t */
  r->f = a1*POW(t, 4.0/5.0);

  if(r->order < 1) return;
  
  r->dfdt = (t > 1e-10) ? a1*4.0/5.0*POW(t, -1.0/5.0) : 0.0;

  if(r->order < 2) return;
  
  r->d2fdt2 = (t > 1e-10) ? -a1*4.0/25.0*POW(t, -6.0/5.0) : 0.0;
}

#include "work_mgga_x.c"

const XC(func_info_type) XC(func_info_mgga_x_lta) = {
  XC_MGGA_X_LTA,
  XC_EXCHANGE,