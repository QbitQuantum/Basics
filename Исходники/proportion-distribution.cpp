// [[Rcpp::export]]
NumericVector cpp_rprop(
    const int& n,
    const NumericVector& size,
    const NumericVector& mean,
    const NumericVector& prior
  ) {
  
  if (std::min({size.length(), mean.length(), prior.length()}) < 1) {
    Rcpp::warning("NAs produced");
    return NumericVector(n, NA_REAL);
  }
  
  NumericVector x(n);
  
  bool throw_warning = false;
  
  for (int i = 0; i < n; i++)
    x[i] = rng_prop(GETV(size, i), GETV(mean, i),
                    GETV(prior, i), throw_warning);
  
  if (throw_warning)
    Rcpp::warning("NAs produced");
  
  return x;
}