static void
F(compile_test) (void)
{
  TYPE a, b, c = 1.0;
  complex TYPE d;
  int i;
  int saved_count;
  long int j;
  long long int k;

  a = cos (cos (x));
  b = acos (acos (a));
  a = sin (sin (x));
  b = asin (asin (a));
  a = tan (tan (x));
  b = atan (atan (a));
  c = atan2 (atan2 (a, c), atan2 (b, x));
  a = cosh (cosh (x));
  b = acosh (acosh (a));
  a = sinh (sinh (x));
  b = asinh (asinh (a));
  a = tanh (tanh (x));
  b = atanh (atanh (a));
  a = exp (exp (x));
  b = log (log (a));
  a = log10 (log10 (x));
  b = ldexp (ldexp (a, 1), 5);
  a = frexp (frexp (x, &i), &i);
  b = expm1 (expm1 (a));
  a = log1p (log1p (x));
  b = logb (logb (a));
  a = exp2 (exp2 (x));
  b = log2 (log2 (a));
  a = pow (pow (x, a), pow (c, b));
  b = sqrt (sqrt (a));
  a = hypot (hypot (x, b), hypot (c, a));
  b = cbrt (cbrt (a));
  a = ceil (ceil (x));
  b = fabs (fabs (a));
  a = floor (floor (x));
  b = fmod (fmod (a, b), fmod (c, x));
  a = nearbyint (nearbyint (x));
  b = round (round (a));
  a = trunc (trunc (x));
  b = remquo (remquo (a, b, &i), remquo (c, x, &i), &i);
  j = lrint (x) + lround (a);
  k = llrint (b) + llround (c);
  a = erf (erf (x));
  b = erfc (erfc (a));
  a = tgamma (tgamma (x));
  b = lgamma (lgamma (a));
  a = rint (rint (x));
  b = nextafter (nextafter (a, b), nextafter (c, x));
  a = nextdown (nextdown (a));
  b = nexttoward (nexttoward (x, a), c);
  a = nextup (nextup (a));
  b = remainder (remainder (a, b), remainder (c, x));
  a = scalb (scalb (x, a), (TYPE) (6));
  k = scalbn (a, 7) + scalbln (c, 10l);
  i = ilogb (x);
  j = llogb (x);
  a = fdim (fdim (x, a), fdim (c, b));
  b = fmax (fmax (a, x), fmax (c, b));
  a = fmin (fmin (x, a), fmin (c, b));
  b = fma (sin (a), sin (x), sin (c));
  a = totalorder (totalorder (x, b), totalorder (c, x));
  b = totalordermag (totalordermag (x, a), totalordermag (c, x));

#ifdef TEST_INT
  a = atan2 (i, b);
  b = remquo (i, a, &i);
  c = fma (i, b, i);
  a = pow (i, c);
#endif
  x = a + b + c + i + j + k;

  saved_count = count;
  if (ccount != 0)
    ccount = -10000;

  d = cos (cos (z));
  z = acos (acos (d));
  d = sin (sin (z));
  z = asin (asin (d));
  d = tan (tan (z));
  z = atan (atan (d));
  d = cosh (cosh (z));
  z = acosh (acosh (d));
  d = sinh (sinh (z));
  z = asinh (asinh (d));
  d = tanh (tanh (z));
  z = atanh (atanh (d));
  d = exp (exp (z));
  z = log (log (d));
  d = sqrt (sqrt (z));
  z = conj (conj (d));
  d = fabs (conj (a));
  z = pow (pow (a, d), pow (b, z));
  d = cproj (cproj (z));
  z += fabs (cproj (a));
  a = carg (carg (z));
  b = creal (creal (d));
  c = cimag (cimag (z));
  x += a + b + c + i + j + k;
  z += d;

  if (saved_count != count)
    count = -10000;

  if (0)
    {
      a = cos (y);
      a = acos (y);
      a = sin (y);
      a = asin (y);
      a = tan (y);
      a = atan (y);
      a = atan2 (y, y);
      a = cosh (y);
      a = acosh (y);
      a = sinh (y);
      a = asinh (y);
      a = tanh (y);
      a = atanh (y);
      a = exp (y);
      a = log (y);
      a = log10 (y);
      a = ldexp (y, 5);
      a = frexp (y, &i);
      a = expm1 (y);
      a = log1p (y);
      a = logb (y);
      a = exp2 (y);
      a = log2 (y);
      a = pow (y, y);
      a = sqrt (y);
      a = hypot (y, y);
      a = cbrt (y);
      a = ceil (y);
      a = fabs (y);
      a = floor (y);
      a = fmod (y, y);
      a = nearbyint (y);
      a = round (y);
      a = trunc (y);
      a = remquo (y, y, &i);
      j = lrint (y) + lround (y);
      k = llrint (y) + llround (y);
      a = erf (y);
      a = erfc (y);
      a = tgamma (y);
      a = lgamma (y);
      a = rint (y);
      a = nextafter (y, y);
      a = nexttoward (y, y);
      a = remainder (y, y);
      a = scalb (y, (const TYPE) (6));
      k = scalbn (y, 7) + scalbln (y, 10l);
      i = ilogb (y);
      j = llogb (y);
      a = fdim (y, y);
      a = fmax (y, y);
      a = fmin (y, y);
      a = fma (y, y, y);
      a = totalorder (y, y);
      a = totalordermag (y, y);

#ifdef TEST_INT
      a = atan2 (i, y);
      a = remquo (i, y, &i);
      a = fma (i, y, i);
      a = pow (i, y);
#endif

      d = cos ((const complex TYPE) z);
      d = acos ((const complex TYPE) z);
      d = sin ((const complex TYPE) z);
      d = asin ((const complex TYPE) z);
      d = tan ((const complex TYPE) z);
      d = atan ((const complex TYPE) z);
      d = cosh ((const complex TYPE) z);
      d = acosh ((const complex TYPE) z);
      d = sinh ((const complex TYPE) z);
      d = asinh ((const complex TYPE) z);
      d = tanh ((const complex TYPE) z);
      d = atanh ((const complex TYPE) z);
      d = exp ((const complex TYPE) z);
      d = log ((const complex TYPE) z);
      d = sqrt ((const complex TYPE) z);
      d = pow ((const complex TYPE) z, (const complex TYPE) z);
      d = fabs ((const complex TYPE) z);
      d = carg ((const complex TYPE) z);
      d = creal ((const complex TYPE) z);
      d = cimag ((const complex TYPE) z);
      d = conj ((const complex TYPE) z);
      d = cproj ((const complex TYPE) z);
    }
}