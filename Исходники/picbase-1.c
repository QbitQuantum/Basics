xsqrt( double x )
{
  __v2df f, g;
  double _d;
  x += x;
  g = __extension__ (__v2df){ x, 0 };
  f = _mm_sqrt_pd( g );
  _d = _mm_cvtsd_f64 (f);
  return (_d);
}