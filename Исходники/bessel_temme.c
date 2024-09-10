int
gsl_sf_bessel_Y_temme(const double nu, const double x,
                      gsl_sf_result * Ynu,
                      gsl_sf_result * Ynup1)
{
  const int max_iter = 15000;
  
  const double half_x = 0.5 * x;
  const double ln_half_x = log(half_x);
  const double half_x_nu = exp(nu*ln_half_x);
  const double pi_nu   = M_PI * nu;
  const double alpha   = pi_nu / 2.0;
  const double sigma   = -nu * ln_half_x;
  const double sinrat  = (fabs(pi_nu) < GSL_DBL_EPSILON ? 1.0 : pi_nu/sin(pi_nu));
  const double sinhrat = (fabs(sigma) < GSL_DBL_EPSILON ? 1.0 : sinh(sigma)/sigma);
  const double sinhalf = (fabs(alpha) < GSL_DBL_EPSILON ? 1.0 : sin(alpha)/alpha);
  const double sin_sqr = nu*M_PI*M_PI*0.5 * sinhalf*sinhalf;
  
  double sum0, sum1;
  double fk, pk, qk, hk, ck;
  int k = 0;
  int stat_iter;

  double g_1pnu, g_1mnu, g1, g2;
  int stat_g = gsl_sf_temme_gamma(nu, &g_1pnu, &g_1mnu, &g1, &g2);

  fk = 2.0/M_PI * sinrat * (cosh(sigma)*g1 - sinhrat*ln_half_x*g2);
  pk = 1.0/M_PI /half_x_nu * g_1pnu;
  qk = 1.0/M_PI *half_x_nu * g_1mnu;
  hk = pk;
  ck = 1.0;

  sum0 = fk + sin_sqr * qk;
  sum1 = pk;

  while(k < max_iter) {
    double del0;
    double del1;
    double gk;
    k++;
    fk  = (k*fk + pk + qk)/(k*k-nu*nu);
    ck *= -half_x*half_x/k;
    pk /= (k - nu);
    qk /= (k + nu);
    gk  = fk + sin_sqr * qk;
    hk  = -k*gk + pk; 
    del0 = ck * gk;
    del1 = ck * hk;
    sum0 += del0;
    sum1 += del1;
    if(fabs(del0) < 0.5*(1.0 + fabs(sum0))*GSL_DBL_EPSILON) break;
  }

  Ynu->val   = -sum0;
  Ynu->err   = (2.0 + 0.5*k) * GSL_DBL_EPSILON * fabs(Ynu->val);
  Ynup1->val = -sum1 * 2.0/x;
  Ynup1->err = (2.0 + 0.5*k) * GSL_DBL_EPSILON * fabs(Ynup1->val);

  stat_iter = ( k >= max_iter ? GSL_EMAXITER : GSL_SUCCESS );
  return GSL_ERROR_SELECT_2(stat_iter, stat_g);
}