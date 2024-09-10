 T pow(const T& x0, int n) const {
  T x = n > 0 ? x0 : invert(x0);
  if (n < 0) n *= -1;
  n %= order(x);
  if (n == 0) return identity();
  int i;
  for (i=1; !(n & i); i <<= 1) x = oper(x,x);
  T agg = x;
  for (i <<= 1, x = oper(x,x); i <= n; i <<= 1, x = oper(x,x))
   if (n & i) agg = oper(agg, x);
  return agg;
 }