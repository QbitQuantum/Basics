// 2x2 (one-sided) Fisher's exact test
// see B. Moore. (2004) On Log Likelihood and the Significance of Rare Events
double fisher_exact(int cfe, int ce, int cf)
{
  assert(cfe <= ce);
  assert(cfe <= cf);

  int a = cfe;
  int b = (cf - cfe);
  int c = (ce - cfe);
  int d = (num_lines - ce - cf + cfe);
  int n = a + b + c + d;

  double cp = exp(lgamma(1+a+c) + lgamma(1+b+d) + lgamma(1+a+b) + lgamma(1+c+d) - lgamma(1+n) - lgamma(1+a) - lgamma(1+b) - lgamma(1+c) - lgamma(1+d));
  double total_p = 0.0;
  int tc = std::min(b,c);
  for (int i=0; i<=tc; i++) {
    total_p += cp;
//      double lg = lgamma(1+a+c) + lgamma(1+b+d) + lgamma(1+a+b) + lgamma(1+c+d) - lgamma(1+n) - lgamma(1+a) - lgamma(1+b) - lgamma(1+c) - lgamma(1+d); double cp = exp(lg);
//      print(a,b,c,d,cp);
    double coef = (double)(b)*(double)(c)/(double)(a+1)/(double)(d+1);
    cp *= coef;
    ++a;
    --c;
    ++d;
    --b;
  }
  return total_p;
}