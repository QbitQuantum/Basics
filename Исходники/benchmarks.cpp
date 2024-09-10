 virtual double fs(arr& g, arr& H, const arr& x) {
   if(&g) { g.resize(x.N); g=1.; }
   if(&H) { H.resize(x.N,x.N); H.setZero(); }
   return sum(x);
 }