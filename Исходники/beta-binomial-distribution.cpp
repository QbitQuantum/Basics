// [[Rcpp::export]]
NumericVector cpp_rbbinom(
    const int& n,
    const NumericVector& size,
    const NumericVector& alpha,
    const NumericVector& beta
  ) {
  
  if (std::min({size.length(), alpha.length(), beta.length()}) < 1) {
    Rcpp::warning("NAs produced");
    return NumericVector(n, NA_REAL);
  }

  NumericVector x(n);
  
  bool throw_warning = false;

  for (int i = 0; i < n; i++)
    x[i] = rng_bbinom(GETV(size, i), GETV(alpha, i), GETV(beta, i),
                      throw_warning);
  
  if (throw_warning)
    Rcpp::warning("NAs produced");

  return x;
}