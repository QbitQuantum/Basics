/* 
 logSumExp_double_by(x):

  1. Scans for the maximum value of x=(x[0], x[by], ..., x[(n-1)*by])
     and copies the values to xx = (xx[0], xx[1], xx[2], ..., xx[n-1]),
     which *must* be preallocated.
  2. Computes result from 'xx'.

  NOTE: The above sweeps the "scattered" 'x' vector only once, and then 
  the "contigous" 'xx' vector once.  This is more likely to create 
  cache hits.
*/
double logSumExp_double_by(double *x, R_xlen_t nx, int narm, int hasna, int by, double *xx) {
  R_xlen_t ii, iMax, idx;
  double xii, xMax;
  LDOUBLE sum;
  int hasna2 = FALSE;  /* Indicates whether NAs where detected or not */

  /* Quick return? */
  if (nx == 0) {
    return(R_NegInf);
  } else if (nx == 1) {
    if (narm && ISNAN(x[0])) {
      return(R_NegInf);
    } else {
      return(x[0]);
    }
  }


  /* To increase the chances for cache hits below, which 
     sweeps through the data twice, we copy data into a
     temporary contigous vector while scanning for the
     maximum value. */

  /* Find the maximum value (and copy) */
  iMax = 0;
  xMax = x[0];
  if (ISNAN(xMax)) hasna2 = TRUE;

  xx[0] = xMax;
  idx = 0;
  for (ii=1; ii < nx; ii++) {
    /* Get the ii:th value */
    idx = idx + by;
    xii = x[idx];

    /* Copy */
    xx[ii] = xii;

    if (hasna && ISNAN(xii)) {
      if (narm) {
        hasna2 = TRUE;
        continue;
      } else {
        return(R_NaReal);
      }
    }

    if (xii > xMax || (narm && ISNAN(xMax))) {
      iMax = ii;
      xMax = xii;
    }

    R_CHECK_USER_INTERRUPT(ii);
  } /* for (ii ...) */


  /* Early stopping? */
  if (ISNAN(xMax)) {
    /* Found only missing values? */
    return narm ? R_NegInf : R_NaReal;
  } else if (xMax == R_PosInf) {
    /* Found +Inf? */
    return(R_PosInf);
  }


  /* Sum differences */
  sum = 0.0;
  for (ii=0; ii < nx; ii++) {
    if (ii == iMax) {
      continue;
    }

    /* Get the ii:th value */
    xii = xx[ii];

    if (!hasna2 || !ISNAN(xii)) {
      sum += exp(xii - xMax);
    }

    R_CHECK_USER_INTERRUPT(ii);
  } /* for (ii ...) */

  sum = xMax + log1p(sum);

  return(sum);
} /* logSumExp_double_by() */