//TODO: Implement variable recovery
//Invert nth Chebyshev-Polynomial of first kind
double invert_Tn(const double value_in){
  const int n = pars -> get_int("DEG");
  //const int n = 8;
  double inv = 0;
  //double tmp = fabs(fmod(value_in,M_PI)-1);
  inv = cosh(1./n*acosh(value_in));
  return inv;
}