  Rcpp::NumericVector rmvnorm(NumericVector mu, NumericMatrix eig_sigma) {
    NumericVector Z = no_init(mu.length());
    for (int i = 0; i < Z.length(); i++)
      Z[i] = R::norm_rand();

    NumericVector X = mu;
    for (int i = 0; i < X.length(); i++) {
      for (int j = 0; j < X.length(); j++) {
        X[i] += eig_sigma(i,j) * Z[j];
      }
    }

    return X;
  }