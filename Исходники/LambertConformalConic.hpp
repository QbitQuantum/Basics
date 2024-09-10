 // Dexp(x,y) = exp((x+y)/2) * 2*sinh((x-y)/2)/(x-y)
 static inline real Dexp(real x, real y) {
   using std::sinh; using std::exp;
   real t = (x - y)/2;
   return (t ? sinh(t)/t : 1) * exp((x + y)/2);
 }