float
__lgamma_negf (float x, int *signgamp)
{
  /* Determine the half-integer region X lies in, handle exact
     integers and determine the sign of the result.  */
  int i = __floorf (-2 * x);
  if ((i & 1) == 0 && i == -2 * x)
    return 1.0f / 0.0f;
  float xn = ((i & 1) == 0 ? -i / 2 : (-i - 1) / 2);
  i -= 4;
  *signgamp = ((i & 2) == 0 ? -1 : 1);

  SET_RESTORE_ROUNDF (FE_TONEAREST);

  /* Expand around the zero X0 = X0_HI + X0_LO.  */
  float x0_hi = lgamma_zeros[i][0], x0_lo = lgamma_zeros[i][1];
  float xdiff = x - x0_hi - x0_lo;

  /* For arguments in the range -3 to -2, use polynomial
     approximations to an adjusted version of the gamma function.  */
  if (i < 2)
    {
      int j = __floorf (-8 * x) - 16;
      float xm = (-33 - 2 * j) * 0.0625f;
      float x_adj = x - xm;
      size_t deg = poly_deg[j];
      size_t end = poly_end[j];
      float g = poly_coeff[end];
      for (size_t j = 1; j <= deg; j++)
	g = g * x_adj + poly_coeff[end - j];
      return __log1pf (g * xdiff / (x - xn));
    }

  /* The result we want is log (sinpi (X0) / sinpi (X))
     + log (gamma (1 - X0) / gamma (1 - X)).  */
  float x_idiff = fabsf (xn - x), x0_idiff = fabsf (xn - x0_hi - x0_lo);
  float log_sinpi_ratio;
  if (x0_idiff < x_idiff * 0.5f)
    /* Use log not log1p to avoid inaccuracy from log1p of arguments
       close to -1.  */
    log_sinpi_ratio = __ieee754_logf (lg_sinpi (x0_idiff)
				      / lg_sinpi (x_idiff));
  else
    {
      /* Use log1p not log to avoid inaccuracy from log of arguments
	 close to 1.  X0DIFF2 has positive sign if X0 is further from
	 XN than X is from XN, negative sign otherwise.  */
      float x0diff2 = ((i & 1) == 0 ? xdiff : -xdiff) * 0.5f;
      float sx0d2 = lg_sinpi (x0diff2);
      float cx0d2 = lg_cospi (x0diff2);
      log_sinpi_ratio = __log1pf (2 * sx0d2
				  * (-sx0d2 + cx0d2 * lg_cotpi (x_idiff)));
    }

  float log_gamma_ratio;
  float y0 = math_narrow_eval (1 - x0_hi);
  float y0_eps = -x0_hi + (1 - y0) - x0_lo;
  float y = math_narrow_eval (1 - x);
  float y_eps = -x + (1 - y);
  /* We now wish to compute LOG_GAMMA_RATIO
     = log (gamma (Y0 + Y0_EPS) / gamma (Y + Y_EPS)).  XDIFF
     accurately approximates the difference Y0 + Y0_EPS - Y -
     Y_EPS.  Use Stirling's approximation.  */
  float log_gamma_high
    = (xdiff * __log1pf ((y0 - e_hi - e_lo + y0_eps) / e_hi)
       + (y - 0.5f + y_eps) * __log1pf (xdiff / y));
  /* Compute the sum of (B_2k / 2k(2k-1))(Y0^-(2k-1) - Y^-(2k-1)).  */
  float y0r = 1 / y0, yr = 1 / y;
  float y0r2 = y0r * y0r, yr2 = yr * yr;
  float rdiff = -xdiff / (y * y0);
  float bterm[NCOEFF];
  float dlast = rdiff, elast = rdiff * yr * (yr + y0r);
  bterm[0] = dlast * lgamma_coeff[0];
  for (size_t j = 1; j < NCOEFF; j++)
    {
      float dnext = dlast * y0r2 + elast;
      float enext = elast * yr2;
      bterm[j] = dnext * lgamma_coeff[j];
      dlast = dnext;
      elast = enext;
    }
  float log_gamma_low = 0;
  for (size_t j = 0; j < NCOEFF; j++)
    log_gamma_low += bterm[NCOEFF - 1 - j];
  log_gamma_ratio = log_gamma_high + log_gamma_low;

  return log_sinpi_ratio + log_gamma_ratio;
}