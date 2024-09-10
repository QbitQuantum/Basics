// [[Rcpp::export]]
NumericVector cpp_rlst(
    const int& n,
    const NumericVector& nu,
    const NumericVector& mu,
    const NumericVector& sigma
  ) {
  
  if (std::min({nu.length(), mu.length(), sigma.length()}) < 1) {
    Rcpp::warning("NAs produced");
    return NumericVector(n, NA_REAL);
  }
  
  NumericVector x(n);
  
  bool throw_warning = false;
  
  for (int i = 0; i < n; i++)
    x[i] = rng_lst(GETV(nu, i), GETV(mu, i),
                   GETV(sigma, i), throw_warning);
  
  if (throw_warning)
    Rcpp::warning("NAs produced");
  
  return x;
}