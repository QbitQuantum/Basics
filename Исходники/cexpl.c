long double complex cexpl (long double complex Z)
{
  long double complex  Res;
  long double rho = expl (__real__ Z);
  __real__ Res = rho * cosl(__imag__ Z);
  __imag__ Res = rho * sinl(__imag__ Z);
  return Res;
}