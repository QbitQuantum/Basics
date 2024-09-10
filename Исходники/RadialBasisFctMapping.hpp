 double evaluate ( double radius ) const
 {
   if (radius >= _r) return 0.0;
   double p = radius / _r;
   using std::pow;
   return pow(1.0-p,8.0) * (32.0*pow(p,3.0) + 25.0*pow(p,2.0) + 8.0*p + 1.0);
 }