mp_int<A,T> pow(const mp_int<A,T>& x, const mp_int<A,T>& y)
{
  if (y.size() == 1)
    return pow(x, y[0]);

  mp_int<A,T> y0(y);
  
  y0.divide_by_2();
  
  mp_int<A,T> y1(y0);

  if (y.is_odd())
    ++y1;

  return pow(x, y0) * pow(x, y1);
}