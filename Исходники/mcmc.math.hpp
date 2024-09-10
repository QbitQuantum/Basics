 double beta_logp(const T& x, const U& alpha, const V& beta) {
   if(!arma::all(x > 0) || !arma::all(x < 1) ||
      !arma::all(alpha > 0) || !arma::all(beta > 0))
     return -std::numeric_limits<double>::infinity();
   return arma::accu(lgamma(alpha+beta) - lgamma(alpha) - lgamma(beta)
                     + schur_product(alpha - 1.0f, log_approx(x))
                     + schur_product(beta - 1.0f, log_approx(1.0f - x)));
 }