double rspfBesselOrderOneFilter::filter(double x, double /* support */)const
{
   double
      p,
      q;
   
   if (x == 0.0)
      return(0.0);
   p=x;
   if (x < 0.0)
      x=(-x);
   if (x < 8.0)
      return(p*J1(x));
   q=sqrt(2.0/(M_PI*x))*(P1(x)*(1.0/sqrt(2.0)*(sin(x)-cos(x)))-8.0/x*Q1(x)*
                         (-1.0/sqrt(2.0)*(sin(x)+cos(x))));
   if (p < 0.0)
      q=(-q);
   return(q);

}