//' Primary production
//' 
//' @export
// [[Rcpp::export]]
NumericVector prod_BeFa(NumericVector chla, NumericVector irrad, NumericVector stemp, NumericVector daylength) {
  NumericVector out(chla.length()); 
  for (int i = 0; i < out.length(); i++) {
    out[i] = opp_befa(chla[i], irrad[i], stemp[i], daylength[i]); 
  }
  return out; 
}