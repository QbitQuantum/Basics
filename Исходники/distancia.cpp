// [[Rcpp::export]]
double distan_def(DataFrame df) {
  
  // access the columns
  NumericVector value = df["value"];
  NumericVector weight = df["weight"];
  NumericVector binary = df["binary"];
  
  int i, n_act = 0, n_oth = 0, n = value.length();
  double actecdf = weight[0], otherecdf = 0, actbin = binary[0], dis = 0;
  
  for(i = 1; i < n; i++){
    dis += (value[i] - value[i-1])*(actecdf - otherecdf)*(actecdf - otherecdf);
    if(binary[i] == actbin){
      actecdf += weight[i];
      n_act++;
      }
    if(binary[i] == 1 - actbin){
      otherecdf += weight[i];
      n_oth++;
      }
  }
  
  // return a distance
  return corregir(n_act, n_oth, dis);
}