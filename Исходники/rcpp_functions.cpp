//' Likelihood function for time-varying microcephaly
//'
//' Calculates the likelihood of observing a vector of microcephaly births given the total number of births and microcephaly probabilities. Note that all vectors must be equal lengths.. Assuming binomial distribution.
//' @param microBirths the vector of observed microcephaly cases over time
//' @param allBirths the corresponding total number of births
//' @param probM the corresponding vector of microcephaly probabilities as calculated by generate_probM.
//' @return a single likelihood value
//' @export
//[[Rcpp::export]]
double likelihood_probM(NumericVector microBirths, NumericVector allBirths, NumericVector probM){
  double lnlik = 0;
  int max = probM.length();
  for(int i = 0; i < max; ++i){
    lnlik += R::dbinom(microBirths[i],allBirths[i],probM[i],1);
  }
  return(lnlik);
}