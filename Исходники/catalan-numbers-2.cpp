unsigned long long detail::BinomialCoefficient::operator()(unsigned n, unsigned k)const
  {
  if(k == 0)
    return 1;

  if(n == 0)
    return 0;

  double product = 1;
  for(unsigned i = 1; i <= k; i++)
    product *= (double(n - (k - i)) / i);
  return (unsigned long long)(floor(product + 0.5));
  }