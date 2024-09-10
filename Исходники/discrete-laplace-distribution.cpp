inline double cdf_dlaplace(double x, double p, double mu,
                           bool& throw_warning) {
#ifdef IEEE_754
  if (ISNAN(x) || ISNAN(p) || ISNAN(mu))
    return x+p+mu;
#endif
  if (p <= 0.0 || p >= 1.0) {
    throw_warning = true;
    return NAN;
  }
  if (x < 0.0) {
    // pow(p, -floor(x-mu))/(1.0+p);
    return exp( (log(p) * -floor(x-mu)) - log1p(p) );
  } else {
    // 1.0 - (pow(p, floor(x-mu)+1.0)/(1.0+p))
    return 1.0 - exp( log(p) * (floor(x-mu)+1.0) - log1p(p) );
  }
} 