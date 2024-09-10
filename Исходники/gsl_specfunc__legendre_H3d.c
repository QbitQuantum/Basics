int
gsl_sf_legendre_H3d_e(const int ell, const double lambda, const double eta,
                         gsl_sf_result * result)
{
  const double abs_lam = fabs(lambda);
  const double lsq     = abs_lam*abs_lam;
  const double xi      = abs_lam * eta;
  const double cosh_eta = cosh(eta);

  /* CHECK_POINTER(result) */

  if(eta < 0.0) {
    DOMAIN_ERROR(result);
  }
  else if(eta > GSL_LOG_DBL_MAX) {
    /* cosh(eta) is too big. */
    OVERFLOW_ERROR(result);
  }
  else if(ell == 0) {
    return gsl_sf_legendre_H3d_0_e(lambda, eta, result);
  }
  else if(ell == 1) {
    return gsl_sf_legendre_H3d_1_e(lambda, eta, result);
  }
  else if(eta == 0.0) {
    result->val = 0.0;
    result->err = 0.0;
    return GSL_SUCCESS;
  }
  else if(xi < 1.0) {
    return legendre_H3d_series(ell, lambda, eta, result);
  }
  else if((ell*ell+lsq)/sqrt(1.0+lsq)/(cosh_eta*cosh_eta) < 5.0*GSL_ROOT3_DBL_EPSILON) {
    /* Large argument.
     */
    gsl_sf_result P;
    double lm;
    int stat_P = gsl_sf_conicalP_large_x_e(-ell-0.5, lambda, cosh_eta, &P, &lm);
    if(P.val == 0.0) {
      result->val = 0.0;
      result->err = 0.0;
      return stat_P;
    }
    else {
      double lnN;
      gsl_sf_result lnsh;
      double ln_abslam;
      double lnpre_val, lnpre_err;
      int stat_e;
      gsl_sf_lnsinh_e(eta, &lnsh);
      legendre_H3d_lnnorm(ell, lambda, &lnN);
      ln_abslam = log(abs_lam);
      lnpre_val  = 0.5*(M_LNPI + lnN - M_LN2 - lnsh.val) - ln_abslam;
      lnpre_err  = lnsh.err;
      lnpre_err += 2.0 * GSL_DBL_EPSILON * (0.5*(M_LNPI + M_LN2 + fabs(lnN)) + fabs(ln_abslam));
      lnpre_err += 2.0 * GSL_DBL_EPSILON * fabs(lnpre_val);
      stat_e = gsl_sf_exp_mult_err_e(lnpre_val + lm, lnpre_err, P.val, P.err, result);
      return GSL_ERROR_SELECT_2(stat_e, stat_P);
    }
  }
  else if(abs_lam > 1000.0*ell*ell) {
    /* Large degree.
     */
    gsl_sf_result P;
    double lm;
    int stat_P = gsl_sf_conicalP_xgt1_neg_mu_largetau_e(ell+0.5,
                                                           lambda,
                                                           cosh_eta, eta,
                                                           &P, &lm);
    if(P.val == 0.0) {
      result->val = 0.0;
      result->err = 0.0;
      return stat_P;
    }
    else {
      double lnN;
      gsl_sf_result lnsh;
      double ln_abslam;
      double lnpre_val, lnpre_err;
      int stat_e;
      gsl_sf_lnsinh_e(eta, &lnsh);
      legendre_H3d_lnnorm(ell, lambda, &lnN);
      ln_abslam = log(abs_lam);
      lnpre_val  = 0.5*(M_LNPI + lnN - M_LN2 - lnsh.val) - ln_abslam;
      lnpre_err  = lnsh.err;
      lnpre_err += GSL_DBL_EPSILON * (0.5*(M_LNPI + M_LN2 + fabs(lnN)) + fabs(ln_abslam));
      lnpre_err += 2.0 * GSL_DBL_EPSILON * fabs(lnpre_val);
      stat_e = gsl_sf_exp_mult_err_e(lnpre_val + lm, lnpre_err, P.val, P.err, result);
      return GSL_ERROR_SELECT_2(stat_e, stat_P);
    }
  }
  else {
    /* Backward recurrence.
     */
    const double coth_eta = 1.0/tanh(eta);
    const double coth_err_mult = fabs(eta) + 1.0;
    gsl_sf_result rH;
    int stat_CF1 = legendre_H3d_CF1_ser(ell, lambda, coth_eta, &rH);
    double Hlm1;
    double Hl    = GSL_SQRT_DBL_MIN;
    double Hlp1  = rH.val * Hl;
    int lp;
    for(lp=ell; lp>0; lp--) {
      double root_term_0 = hypot(lambda,lp);
      double root_term_1 = hypot(lambda,lp+1.0);
      Hlm1 = ((2.0*lp + 1.0)*coth_eta*Hl - root_term_1 * Hlp1)/root_term_0;
      Hlp1 = Hl;
      Hl   = Hlm1;
    }

    if(fabs(Hl) > fabs(Hlp1)) {
      gsl_sf_result H0;
      int stat_H0 = gsl_sf_legendre_H3d_0_e(lambda, eta, &H0);
      result->val  = GSL_SQRT_DBL_MIN/Hl * H0.val;
      result->err  = GSL_SQRT_DBL_MIN/fabs(Hl) * H0.err;
      result->err += fabs(rH.err/rH.val) * (ell+1.0) * coth_err_mult * fabs(result->val);
      result->err += 2.0 * GSL_DBL_EPSILON * fabs(result->val);
      return GSL_ERROR_SELECT_2(stat_H0, stat_CF1);
    }
    else {
      gsl_sf_result H1;
      int stat_H1 = gsl_sf_legendre_H3d_1_e(lambda, eta, &H1);
      result->val  = GSL_SQRT_DBL_MIN/Hlp1 * H1.val;
      result->err  = GSL_SQRT_DBL_MIN/fabs(Hlp1) * H1.err;
      result->err += fabs(rH.err/rH.val) * (ell+1.0) * coth_err_mult * fabs(result->val);
      result->err += 2.0 * GSL_DBL_EPSILON * fabs(result->val);
      return GSL_ERROR_SELECT_2(stat_H1, stat_CF1);
    }
  }
}