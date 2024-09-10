// [[Rcpp::export]]
double getlambdashrinkC(NumericVector y) {
  double n=0;
  int m=y.length();
  double lambda;
  for (int i=0;i<m;i++) {
    n+=y[i];
  }
  NumericVector u=y/n;


  NumericVector temp(m,1.0);
  NumericVector varu=u*(temp-u)/(n-1);

  double msp=0;
  for (int i=0;i<m;i++) {
    msp+=pow(u[i]-(1.0/m),2);
  }
  if (msp==0) {
    lambda=1;
  } else {
    lambda=0;
    for (int i=0;i<m;i++) {
    lambda+=varu[i];
    }
    lambda=lambda/msp;
  }
  if (lambda>1) {
    lambda=1;
  }
  if (lambda<0) {
    lambda=0;
  }
  return lambda;
}