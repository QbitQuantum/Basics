long double complex
ctanl (long double complex a)
{
  long double rt, it;
  long double complex n, d;

  rt = tanl (REALPART (a));
  it = tanhl (IMAGPART (a));
  COMPLEX_ASSIGN (n, rt, it);
  COMPLEX_ASSIGN (d, 1, - (rt * it));

  return n / d;
}