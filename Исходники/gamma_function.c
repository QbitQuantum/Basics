////////////////////////////////////////////////////////////////////////////////
// static long double Duplication_Formula(long double two_x)                  //
//                                                                            //
//  Description:                                                              //
//     This function returns the Gamma(two_x) using the duplication formula   //
//     Gamma(2x) = (2^(2x-1) / sqrt(pi)) Gamma(x) Gamma(x+1/2).               //
//                                                                            //
//  Arguments:                                                                //
//     none                                                                   //
//                                                                            //
//  Return Values:                                                            //
//     Gamma(two_x)                                                           //
//                                                                            //
//  Example:                                                                  //
//     long double two_x, g;                                                  //
//                                                                            //
//     g = Duplication_Formula(two_x);                                        //
////////////////////////////////////////////////////////////////////////////////
static long double Duplication_Formula( long double two_x )
{
   long double x = 0.5L * two_x;
   long double g;
   double two_n = 1.0;
   int n = (int) two_x - 1;

   g = powl(2.0L, two_x - 1.0L - (long double) n);
   g = ldexpl(g,n);
   g /= sqrt(pi);
   g *= xGamma_Function(x);
   g *= xGamma_Function(x + 0.5L);

   return g;
}