NumericVector pow2(NumericVector v){
  int n = v.length();
  NumericVector out(n);
  for(int j = 0; j < n; j++)
    out(j) = v(j) * v(j);

  return( out );
}