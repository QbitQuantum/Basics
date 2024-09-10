float epsF(float x) {
   x = copysignf(x, 1.0);
   float y = nextafterf(x, INFINITY);
   return y-x;
}