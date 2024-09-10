 static inline real Dgd(real x, real y) {
   using std::sinh;
   return Datan(sinh(x), sinh(y)) * Dsinh(x, y);
 }