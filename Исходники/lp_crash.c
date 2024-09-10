MYBOOL __WINAPI guess_basis(lprec *lp, REAL *guessvector, int *basisvector)
{
  MYBOOL *isnz = NULL, status = FALSE;
  REAL   *values = NULL, *violation = NULL,
         eps = lp->epsprimal,
         *value, error, upB, loB, sortorder = -1.0;
  int    i, j, jj, n, *rownr, *colnr, *slkpos = NULL,
         nrows = lp->rows, ncols = lp->columns, nsum = lp->sum;
  int    *basisnr;
  MATrec *mat = lp->matA;

  if(!mat_validate(mat))
    return( status );

  /* Create helper arrays, providing for multiple use of the violation array */
  if(!allocREAL(lp, &values, nsum+1, TRUE) ||
     !allocREAL(lp, &violation, nsum+1, TRUE))
    goto Finish;

  /* Compute the values of the constraints for the given guess vector */
  i = 0;
  n = get_nonzeros(lp);
  rownr = &COL_MAT_ROWNR(i);
  colnr = &COL_MAT_COLNR(i);
  value = &COL_MAT_VALUE(i);
  for(; i < n; i++, rownr += matRowColStep, colnr += matRowColStep, value += matValueStep)
    values[*rownr] += unscaled_mat(lp, my_chsign(is_chsign(lp, *rownr), *value), *rownr, *colnr) *
                      guessvector[*colnr];
  MEMMOVE(values+nrows+1, guessvector+1, ncols);

  /* Initialize bound "violation" or primal non-degeneracy measures, expressed
     as the absolute value of the differences from the closest bound. */
  for(i = 1; i <= nsum; i++) {
    if(i <= nrows) {
      loB = get_rh_lower(lp, i);
      upB = get_rh_upper(lp, i);
    }
    else {
      loB = get_lowbo(lp, i-nrows);
      upB = get_upbo(lp, i-nrows);
    }

    /* Free constraints/variables */
    if(my_infinite(lp, loB) && my_infinite(lp, upB))
      error = 0;
    /* Violated constraints/variable bounds */
    else if(values[i]+eps < loB)
      error = loB-values[i];
    else if(values[i]-eps > upB)
      error = values[i]-upB;
    /* Non-violated constraints/variables bounds */
    else if(my_infinite(lp, upB))
      error = MAX(0, values[i]-loB);
    else if(my_infinite(lp, loB))
      error = MAX(0, upB-values[i]);
    else
      error = MIN(upB-values[i], values[i]-loB); /* MAX(upB-values[i], values[i]-loB); */
    if(error != 0)
      violation[i] = sortorder*error;
    basisvector[i] = i;
  }

  /* Sort decending , meaning that variables with the largest
     "violations" will be designated basic. Effectively, we are performing a
     greedy type algorithm, but start at the "least interesting" end. */
  sortByREAL(basisvector, violation, nsum, 1, FALSE);
  error = violation[1]; /* Used for setting the return value */

  /* Let us check for obvious row singularities and try to fix these.
     Note that we reuse the memory allocated to the violation array.
     First assemble necessary basis statistics... */
  slkpos = (int *) violation;
  n = nrows+1;
  MEMCLEAR(slkpos, n);
  isnz = (MYBOOL *) (slkpos+n+1);
  MEMCLEAR(isnz, n);
  for(i = 1; i <= nrows; i++) {
    j = abs(basisvector[i]);
    if(j <= nrows) {
      isnz[j] = TRUE;
      slkpos[j] = i;
    }
    else {
      j-= nrows;
      jj = mat->col_end[j-1];
      jj = COL_MAT_ROWNR(jj);
      isnz[jj] = TRUE;
    }
  }
  for(; i <= nsum; i++) {
    j = abs(basisvector[i]);
    if(j <= nrows)
      slkpos[j] = i;
  }

  /* ...then set the corresponding slacks basic for row rank deficient positions */
  for(j = 1; j <= nrows; j++) {
    if(slkpos[j] == 0)
      report(lp, SEVERE, "guess_basis: Internal error");
    if(!isnz[j]) {
      isnz[j] = TRUE;
      i = slkpos[j];
      swapINT(&basisvector[i], &basisvector[j]);
      basisvector[j] = abs(basisvector[j]);
    }
  }

  /* Adjust the non-basic indeces for the (proximal) bound state */
  for(i = nrows+1, basisnr = basisvector+i; i <= nsum; i++, basisnr++) {
    n = *basisnr;
    if(n <= nrows) {
      values[n] -= get_rh_lower(lp, n);
      if(values[n] <= eps)
        *basisnr = -(*basisnr);
    }
    else
      if(values[n]-eps <= get_lowbo(lp, n-nrows))
        *basisnr = -(*basisnr);
  }

/* Lastly normalize all basic variables to be coded as lower-bounded,
   or effectively zero-based in the case of free variables. */
  for(i = 1; i <= nrows; i++)
    basisvector[i] = -abs(basisvector[i]);

  /* Clean up and return status */
  status = (MYBOOL) (error <= eps);
Finish:
  FREE(values);
  FREE(violation);

  return( status );
}