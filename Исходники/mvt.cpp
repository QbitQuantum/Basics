  //======================================================================
  double dmvt(const Vector &x,  const Vector &mu, const SpdMatrix &Siginv, double nu,
	      double ldsi, bool logscale){
    long dim = mu.size();
    double nc = lgamma( (nu + dim)/2.0 ) + .5 * ldsi
        - lgamma(nu/2.0) - (.5*dim) * (log(nu) + Constants::log_pi);
    double delta = Siginv.Mdist(x, mu);
    double ans = nc - .5*(nu + dim)*(::log1p(delta/nu));
    return logscale ? ans : exp(ans);
  }