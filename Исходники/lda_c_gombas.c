#include <stdio.h>
#include "util.h"

/************************************************************************
 Wigner's parametrization from the low density limit
************************************************************************/

#define XC_LDA_C_GOMBAS  24   /* Gombas parametrization       */

static inline void 
func(const XC(func_type) *p, XC(lda_work_t) *r)
{
  static FLOAT a1=-0.0357, a2=0.0562, b1=-0.0311, b2=2.39;
  FLOAT t1, t2, cnst_rs, x;
  
  cnst_rs = CBRT(4.0*M_PI/3.0);
  x = cnst_rs*r->rs[1];

  t1 = 1.0 + a2*x;
  t2 = x + b2;

  r->zk = a1/t1 + b1*LOG(t2/x);

  if(r->order < 1) return;

  r->dedrs = -a1*a2/(t1*t1) - b1*b2/(x*t2);
  r->dedrs*= cnst_rs;
  r->dedz  = 0.0;

  if(r->order < 2) return;
