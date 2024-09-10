void
math (double d, int *ex, double *dp)
{
  acos (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 8 } */
  acosh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 10 } */
  asin (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 12 } */
  asinh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 14 } */
  atan (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 16 } */
  atanh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 18 } */
  atan2 (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 20 } */
  cbrt (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 22 } */
  ceil (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 24 } */
  copysign (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 26 } */
  cos (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 28 } */
  cosh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 30 } */
  erf (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 32 } */
  erfc (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 34 } */
  exp (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 36 } */
  exp2 (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 38 } */
  expm1 (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 40 } */
  fabs (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 42 } */
  fdim (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 44 } */
  floor (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 46 } */
  fma (d, d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 48 } */
  fmax (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 50 } */
  fmin (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 52 } */
  fmod (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 54 } */
  frexp (d, ex); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 56 } */
  hypot (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 58 } */
  /* We don't generate the warning for ilogb.  */
  ilogb (d);
  ldexp (d, *ex); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 62 } */
  lgamma (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 64 } */
  llrint (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 66 } */
  llround (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 68 } */
  log (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 70 } */
  log10 (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 72 } */
  log1p (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 74 } */
  log2 (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 76 } */
  logb (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 78 } */
  lrint (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 80 } */
  lround (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 82 } */
  modf (d, dp); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 84 } */
  nan (""); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 86 } */
  nearbyint (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 88 } */
  nextafter (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 90 } */
  nexttoward (d, 20.0L); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 92 } */
  pow (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 94 } */
  remainder (d, d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 96 } */
  remquo (d, d, ex); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 98 } */
  rint (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 100 } */
  round (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 102 } */
  scalbln (d, 100L); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 104 } */
  scalbn (d, 100); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 106 } */
  sin (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 108 } */
  sinh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 110 } */
  sincos (d, dp, dp); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 112 } */
  sqrt (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 114 } */
  tan (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 116 } */
  tanh (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 118 } */
  tgamma (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 120 } */
  trunc (d); /* { dg-warning "incompatible implicit" } */
  /* { dg-message "include ..math.h.." "" { target *-*-* } 122 } */
}