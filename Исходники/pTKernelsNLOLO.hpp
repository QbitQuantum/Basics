//------------------------------------------------------------------------------
inline double pTIgqPqq::regularIntegral(double y)
{
   if (y == 0. || y == 1.)
      return 0.;
   return y*log(y)*(2. - y) + 0.5*std::pow(-1. + y, 2)*log1p(-y);
}