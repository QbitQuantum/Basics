/*To set the initial value of pr, it must hold $g_{\mu\nu}p^{\mu}p^{\nu} = 0$.
This factor multiplies p0 to guarantee that p1 fulfill the null geodesic condition.*/
mydbl condition_factor(mydbl r, double a)
{
  return (mydbl)(1.0/a)*sqrtl((1.0+2.0*potential(r)/(C*C))/(1.0 - 2.0*potential(r)/(C*C)));
}