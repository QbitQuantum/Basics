static inline int
LL98 (double psi[], const int two_nmin, const int two_nmax, void *params,
      double (*X) (const double, const void *),
      double (*Y) (const double, const void *),
      double (*Z) (const double, const void *),
      void (*normalize) (double *, const double, const int, const void *))
/* This is the generic LL98 recurssion strategy common to the 3j and 6j
   calculations. */
{
  int nmax_idx = (two_nmax - two_nmin) / 2;
  int ndim = nmax_idx + 1, nminus_idx = 0, nplus_idx = nmax_idx, i;
  bool iter_up = true, iter_down = true;
  double y;
  double nmin = two_nmin / 2.0, nmax = two_nmax / 2.0;
  double rs[ndim];

  if (ndim == 1)		/* Only a single value is possible, requires special handling. */
    {
      psi[0] = 1.0;
      normalize (psi, nmin, nmax_idx, params);
      return __SUCCESS;
    }

  /* Iterate LL98 Eq. 3 from nmin upwards unless the first term is undefined. */
  y = Y (nmin, params);

  if (fabs (y) > __SMALL)
    {
      rs[0] = -X (nmin, params) / y;

      for (i = 1; i <= nmax_idx; i++)
	{
	  double n, denom;

	  if (rs[i - 1] > 1.0)
	    {
	      nminus_idx = i - 1;
	      break;
	    }

	  n = nmin + i;
	  denom = Y (n, params) + Z (n, params) * rs[i - 1];

	  if (fabs (denom) > __SMALL)
	    rs[i] = -X (n, params) / denom;
	  else
	    {
	      nminus_idx = i - 1;
	      break;
	    }
	}

      /* Generate psi(n_minus-k)/psi(n_minus) == Psi_minus(n) using LL98
         Eq. 5'. */
      if (nminus_idx > 0)
	{
	  psi[nminus_idx - 1] = rs[nminus_idx - 1];

	  for (i = nminus_idx - 2; i >= 0; i--)
	    psi[i] = psi[i + 1] * rs[i];
	}
    }
  else
    {
      /* If Y is zero there are two possibilities: 

         a) X != 0. In this case, first term s(nmin) is infinity because
         psi(nmin + 1) = 0. However, psi(nmin) is not nescessarily 0 in this
         case though. This implies we're actually in the classically allowed
         region at nmin, and so we can later use the 3 term recursion to iterate
         up from nmin.

         b) X = 0. In this case the first term is undefined, and we're unable to
         iterate upwards from nmin using either the 2 or 3 term recursions. */
      nminus_idx = 0;

      if (fabs (X (nmin, params)) < __SMALL)
	iter_up = false;
    }

  /* Iterate LL98 Eq. 2 from nmax downwards, unless the first term is undefined. */
  y = Y (nmax, params);

  if (fabs (y) > __SMALL)
    {
      rs[nmax_idx] = -Z (nmax, params) / y;

      for (i = nmax_idx - 1; i > nminus_idx; i--)
	{
	  double n, denom;

	  if (rs[i + 1] > 1.0)
	    {
	      nplus_idx = i + 1;
	      break;
	    }

	  n = nmin + i;

	  denom = Y (n, params) + X (n, params) * rs[i + 1];

	  if (fabs (denom) > __SMALL)
	    rs[i] = -Z (n, params) / denom;
	  else
	    {
	      nplus_idx = i + 1;
	      break;
	    }
	}

      /* Generate psi(n_plus+k)/psi(n_plus) == Psi_plus(n) using LL98 Eq. 4'. */
      if (nplus_idx < nmax_idx)
	{
	  psi[nplus_idx + 1] = rs[nplus_idx + 1];

	  for (i = nplus_idx + 2; i <= nmax_idx; i++)
	    psi[i] = psi[i - 1] * rs[i];
	}
    }
  else
    {
      /* If Y is zero there are two possibilities: 

         a) Z != 0. In this case, first term r(nmax) is infinity because
         psi(nmax - 1) = 0. However, psi(nmax) is not nescessarily 0 in this
         case though. This implies we're actually in the classically allowed
         region at nmax, and so we can later use the 3 term recursion to iterate
         up from nmin.

         b) Z = 0. In this case the first term is undefined, and we're unable to
         iterate upwards from nmin using either the 2 or 3 term recursions. */
      nplus_idx = nmax_idx;

      if (fabs (Z (nmax, params)) < __SMALL)
	iter_down = false;
    }

  /* Iterate in the classical region using three term recursion LL98 Eq. 1.  */
  if (iter_up)			/* Iterate upwards from nminus, chosing nc = nplus. */
    {
      double a;
      int iter_up_start_idx;

      /* Note that this initialization stuff can't be done inside the logic of
         iterating LL98 Eq. 3 above, since it can potentially be clobbered during
         the subsequent iteration of LL98 Eq. 4 if that section was also to
         contain initialization logic for iterating downwards in the classical
         region below. Really, tempting though it is, don't move this earlier. */
      if (nminus_idx < 2)
	{
	  psi[0] = 1.0;
	  psi[1] = -Y (nmin, params) / X (nmin, params);	/* Since psi(nmin - 1) = 0 */
	  iter_up_start_idx = 2;
	}
      else
	{
	  psi[nminus_idx] = 1.0;
	  iter_up_start_idx = nminus_idx + 1;
	}

      for (i = iter_up_start_idx; i <= nplus_idx; i++)
	{
	  double nn = nmin - 1.0 + i;	/* n - 1 */
	  psi[i] = -(Y (nn, params) * psi[i - 1] +
		      Z (nn, params) * psi[i - 2]) / X (nn, params);
	}

      /* Since we choose nc=nplus, Psi_plus(nc)=1, and we multiply
         Psi_minus(nmin...nplus) by Psi_plus(nc)/Psi_minus(nc) ==
         1/Psi_minus(n_plus) to give us Psi_plus(nmin...nplus). */
      a = 1.0 / psi[nplus_idx];

      for (i = 0; i <= nplus_idx; i++)
	psi[i] *= a;

      normalize (psi, nmin, nmax_idx, params);
      return __SUCCESS;
    }

  if (iter_down)		/* Iterate downwards from nplus, chosing nc = nminus. */
    {
      double a;
      int iter_down_start_idx;

      /* Note that this initialization stuff could be done inside the logic of
         iterating LL98 Eq. 2 above. However following that design leads to some
         rather obscure corner cases and errors, so it's cleaner to do it
         here. Really, don't move it. */
      if (nplus_idx > nmax_idx - 2)
	{
	  psi[nplus_idx] = 1.0;
	  psi[nplus_idx - 1] = -Y (nmax, params) / Z (nmax, params);
	  iter_down_start_idx = nplus_idx - 2;
	}
      else
	{
	  psi[nplus_idx] = 1.0;
	  iter_down_start_idx = nplus_idx - 1;
	}

      for (i = iter_down_start_idx; i >= nminus_idx; i--)
	{
	  double nn = nmin + 1.0 + i;	/* n + 1 */
	  psi[i] = -(X (nn, params) * psi[i + 2] +
		      Y (nn, params) * psi[i + 1]) / Z (nn, params);
	}

      /* Since we choose nc=nminus, Psi_minus(nc)=1, and we multiply
         Psi_plus(nminus...nmax) by Psi_minus(nc)/Psi_plus(nc) ==
         1/Psi_plus(n_plus) to give us Psi_minus(nminus...nmax). */
      a = 1.0 / psi[nminus_idx];

      for (i = nmax_idx; i >= nminus_idx; i--)
	psi[i] *= a;

      normalize (psi, nmin, nmax_idx, params);
      return __SUCCESS;
    }

  fprintf (stderr, "LL98: Could not iterate in either direction\n");
  return __FAILURE;

}