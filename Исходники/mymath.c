static long double Continued_Fraction_Ei( long double x )
{
   long double Am1 = 1.0L;
   long double A0 = 0.0L;
   long double Bm1 = 0.0L;
   long double B0 = 1.0L;
   long double a = expl(x);
   long double b = -x + 1.0L;
   long double Ap1 = b * A0 + a * Am1;
   long double Bp1 = b * B0 + a * Bm1;
   int j = 1;

   a = 1.0L;
   while ( fabsl(Ap1 * B0 - A0 * Bp1) > epsilon * fabsl(A0 * Bp1) ) {
      if ( fabsl(Bp1) > 1.0L) {
         Am1 = A0 / Bp1;
         A0 = Ap1 / Bp1;
         Bm1 = B0 / Bp1;
         B0 = 1.0L;
      } else {
         Am1 = A0;
         A0 = Ap1;
         Bm1 = B0;
         B0 = Bp1;
      }
      a = -j * j;
      b += 2.0L;
      Ap1 = b * A0 + a * Am1;
      Bp1 = b * B0 + a * Bm1;
      j += 1;
   }
   return (-Ap1 / Bp1);
}