/* tanh(z) = (tanh(a) + itan(b)) / (1 - itanh(a)tan(b))  */
GFC_COMPLEX_4
ctanhf (GFC_COMPLEX_4 a)
{
  GFC_REAL_4 rt;
  GFC_REAL_4 it;
  GFC_COMPLEX_4 n;
  GFC_COMPLEX_4 d;

  rt = tanhf (REALPART (a));
  it = tanf (IMAGPART (a));
  COMPLEX_ASSIGN (n, rt, it);
  COMPLEX_ASSIGN (d, 1, - (rt * it));

  return n / d;
}