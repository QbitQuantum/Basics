// [[Rcpp::export]]
NumericVector calc_rr_cds(NumericVector outcome, NumericMatrix covars) {
  int nrow = covars.nrow(), ncol = covars.ncol();
  if (outcome.length() != nrow) {
    stop("length of outcome should be the same as the number of rows in covars");
  }
  
  NumericVector out(ncol);
  out.attr("names") = colnames(covars);
  
  for (int j = 0; j < ncol; j++) {
    double outcomes1 = 0;
    double outcomes0 = 0;
    double n1 = 0;
    double n0 = 0;
        
    for (int i = 0; i < nrow; i++) {
      double covar = covars(i,j);
      if (covar == 0.0) {
        n0 += 1;
        outcomes0 += outcome(i);
      } else {
        n1 += 1;
        outcomes1 += outcome(i);
      }
    }
    
    double prev1 = outcomes1/n1;
    double prev0 = outcomes0/n0;
    
    double rr = prev1/prev0;
    out(j) = rr;
  }
  return out;
}