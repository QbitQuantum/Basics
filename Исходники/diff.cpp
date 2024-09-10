// [[Rcpp::export]]
NumericVector diff_cpp(const NumericVector x, const int lag = 1) {
  int n = x.length();
  NumericVector y(n - lag);
  for (int i = lag; i < n; i++) {
    y[i - lag] = x[i] - x[i - lag];
  }
  return y;
}