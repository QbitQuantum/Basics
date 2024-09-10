int
gsl_sf_bessel_jl_e(const int l, const double x, gsl_sf_result * result)
{
  if(l < 0 || x < 0.0) {
    DOMAIN_ERROR(result);
  }
  else if(x == 0.0) {
    result->val = ( l > 0 ? 0.0 : 1.0 );
    result->err = 0.0;
    return GSL_SUCCESS;
  }
  else if(l == 0) {
    return gsl_sf_bessel_j0_e(x, result);
  }
  else if(l == 1) {
    return gsl_sf_bessel_j1_e(x, result);
  }
  else if(l == 2) {
    return gsl_sf_bessel_j2_e(x, result);
  }
  else if(x*x < 10.0*(l+0.5)/M_E) {
    gsl_sf_result b;
    int status = gsl_sf_bessel_IJ_taylor_e(l+0.5, x, -1, 50, GSL_DBL_EPSILON, &b);
    double pre   = sqrt((0.5*M_PI)/x);
    result->val  = pre * b.val;
    result->err  = pre * b.err;
    result->err += 2.0 * GSL_DBL_EPSILON * fabs(result->val);
    return status;
  }
  else if(GSL_ROOT3_DBL_EPSILON * x > (l*l + l + 1.0)) {
    gsl_sf_result b;
    int status = gsl_sf_bessel_Jnu_asympx_e(l + 0.5, x, &b);
    double pre = sqrt((0.5*M_PI)/x);
    result->val = pre * b.val;
    result->err = 2.0 * GSL_DBL_EPSILON * fabs(result->val) + pre * b.err;
    return status;
  }
  else if(l > 1.0/GSL_ROOT6_DBL_EPSILON) {
    gsl_sf_result b;
    int status = gsl_sf_bessel_Jnu_asymp_Olver_e(l + 0.5, x, &b);
    double pre = sqrt((0.5*M_PI)/x);
    result->val = pre * b.val;
    result->err = 2.0 * GSL_DBL_EPSILON * fabs(result->val) + pre * b.err;
    return status;
  }
  else {
    double sgn;
    double ratio;
    int stat_CF1 = gsl_sf_bessel_J_CF1(l+0.5, x, &ratio, &sgn);
    double jellp1 = GSL_SQRT_DBL_EPSILON * ratio;
    double jell   = GSL_SQRT_DBL_EPSILON;
    double jellm1;
    int ell;
    for(ell = l; ell > 0; ell--) {
      jellm1 = -jellp1 + (2*ell + 1)/x * jell;
      jellp1 = jell;
      jell   = jellm1;
    }

    if(fabs(jell) > fabs(jellp1)) {
      gsl_sf_result j0_result;
      int stat_j0  = gsl_sf_bessel_j0_e(x, &j0_result);
      double pre   = GSL_SQRT_DBL_EPSILON / jell;
      result->val  = j0_result.val * pre;
      result->err  = j0_result.err * fabs(pre);
      result->err += 2.0 * GSL_DBL_EPSILON * (0.5*l + 1.0) * fabs(result->val);
      return GSL_ERROR_SELECT_2(stat_j0, stat_CF1);
    }
    else {
      gsl_sf_result j1_result;
      int stat_j1  = gsl_sf_bessel_j1_e(x, &j1_result);
      double pre   = GSL_SQRT_DBL_EPSILON / jellp1;
      result->val  = j1_result.val * pre;
      result->err  = j1_result.err * fabs(pre);
      result->err += 2.0 * GSL_DBL_EPSILON * (0.5*l + 1.0) * fabs(result->val);
      return GSL_ERROR_SELECT_2(stat_j1, stat_CF1);
    }
  }
}