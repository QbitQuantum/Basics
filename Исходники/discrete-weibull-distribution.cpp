inline double invcdf_dweibull(double p, double q, double beta,
                              bool& throw_warning) {
#ifdef IEEE_754
  if (ISNAN(p) || ISNAN(q) || ISNAN(beta))
    return p+q+beta;
#endif
  if (q <= 0.0 || q >= 1.0 || beta <= 0.0 || !VALID_PROB(p)) {
    throw_warning = true;
    return NAN;
  }
  if (p == 0.0)
    return 0.0;
  return ceil(pow(log(1.0 - p)/log(q), 1.0/beta) - 1.0);
}