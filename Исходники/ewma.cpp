NumericVector ewma(
    const NumericVector& x,
    const double& lambda = 0.2,
    const bool& na_prev = true
  ) {
  
  if (lambda < 0 || lambda > 1) {
    Rcpp::stop("lambda takes values between 0 and 1");
  }
  
  int n = x.length();
  NumericVector z(n, NA_REAL);
  z[0] = x[0];
  
  for ( int i = 1; i < n; i++ ) {
    if (R_IsNA(x[i])) {
      if (na_prev) {
        z[i] = z[i-1];
        continue;
      } else {
        break;
      }
    }
    z[i] = lambda * x[i] + (1 - lambda) * z[i-1];
  }
  
  return z;
}