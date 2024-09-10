double
gsl_cdf_gamma_Pinv (const double P, const double a, const double b)
{
  double x;

  if (P == 1.0)
    {
      return GSL_POSINF;
    }
  else if (P == 0.0)
    {
      return 0.0;
    }

  /* Consider, small, large and intermediate cases separately.  The
     boundaries at 0.05 and 0.95 have not been optimised, but seem ok
     for an initial approximation.

     BJG: These approximations aren't really valid, the relevant
     criterion is P*gamma(a+1) < 1. Need to rework these routines and
     use a single bisection style solver for all the inverse
     functions.
  */

  if (P < 0.05)
    {
      double x0 = exp ((gsl_sf_lngamma (a) + log (P)) / a);
      x = x0;
    }
  else if (P > 0.95)
    {
      double x0 = -log1p (-P) + gsl_sf_lngamma (a);
      x = x0;
    }
  else
    {
      double xg = gsl_cdf_ugaussian_Pinv (P);
      double x0 = (xg < -0.5*sqrt (a)) ? a : sqrt (a) * xg + a;
      x = x0;
    }

  /* Use Lagrange's interpolation for E(x)/phi(x0) to work backwards
     to an improved value of x (Abramowitz & Stegun, 3.6.6) 

     where E(x)=P-integ(phi(u),u,x0,x) and phi(u) is the pdf.
   */

  {
    double lambda, dP, phi;
    unsigned int n = 0;

  start:
    dP = P - gsl_cdf_gamma_P (x, a, 1.0);
    phi = gsl_ran_gamma_pdf (x, a, 1.0);

    if (dP == 0.0 || n++ > 32)
      goto end;

    lambda = dP / GSL_MAX (2 * fabs (dP / x), phi);

    {
      double step0 = lambda;
      double step1 = -((a - 1) / x - 1) * lambda * lambda / 4.0;

      double step = step0;
      if (fabs (step1) < 0.5 * fabs (step0))
        step += step1;

      if (x + step > 0)
        x += step;
      else
        {
          x /= 2.0;
        }

      if (fabs (step0) > 1e-10 * x || fabs(step0 * phi) > 1e-10 * P)
        goto start;
    }

  end:
    if (fabs(dP) > GSL_SQRT_DBL_EPSILON * P)
      {
        GSL_ERROR_VAL("inverse failed to converge", GSL_EFAILED, GSL_NAN);
      }
    
    return b * x;
  }
}