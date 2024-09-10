float cpp_rana(double* vals, long sz, double* weights){
  //The rana function! It does more things! Wow!
  double tot = 512.0, x, y;
  for(long i = 0; i < sz; ++i){
    x = vals[i];
    if(i == (sz - 1)){
      y = vals[0];
    }
    else{
      y = vals[i + 1];
    }
    tot += weights[i] * (x * sin(sqrt(abs(y + 1 - x))) * cos(sqrt(abs(x + y + 1)))
			 + (y + 1) * cos(sqrt(abs(y + 1 - x))) * sin(sqrt(abs(x + y + 1))));
  }
  return tot;
}