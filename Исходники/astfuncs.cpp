static double kepler( const double ecc, double mean_anom)
{
   double curr, err, thresh, offset = 0.;
   double delta_curr = 1.;
   bool is_negative = false;
   unsigned n_iter = 0;

   if( !mean_anom)
      return( 0.);

   if( ecc < 1.)
      {
      if( mean_anom < -PI || mean_anom > PI)
         {
         double tmod = fmod( mean_anom, PI * 2.);

         if( tmod > PI)             /* bring mean anom within -pi to +pi */
            tmod -= 2. * PI;
         else if( tmod < -PI)
            tmod += 2. * PI;
         offset = mean_anom - tmod;
         mean_anom = tmod;
         }

      if( ecc < .9)     /* low-eccentricity formula from Meeus,  p. 195 */
         {
         curr = atan2( sin( mean_anom), cos( mean_anom) - ecc);
         do
            {
            err = (curr - ecc * sin( curr) - mean_anom) / (1. - ecc * cos( curr));
            curr -= err;
            }
            while( fabs( err) > THRESH);
         return( curr + offset);
         }
      }


   if( mean_anom < 0.)
      {
      mean_anom = -mean_anom;
      is_negative = true;
      }

   curr = mean_anom;
   thresh = THRESH * fabs( 1. - ecc);
               /* Due to roundoff error,  there's no way we can hope to */
               /* get below a certain minimum threshhold anyway:        */
   if( thresh < MIN_THRESH)
      thresh = MIN_THRESH;
   if( (ecc > .8 && mean_anom < PI / 3.) || ecc > 1.)    /* up to 60 degrees */
      {
      double trial = mean_anom / fabs( 1. - ecc);

      if( trial * trial > 6. * fabs(1. - ecc))   /* cubic term is dominant */
         {
         if( mean_anom < PI)
            trial = CUBE_ROOT( 6. * mean_anom);
         else        /* hyperbolic w/ 5th & higher-order terms predominant */
            trial = asinh( mean_anom / ecc);
         }
      curr = trial;
      if( thresh > THRESH)       /* happens if e > 2. */
         thresh = THRESH;
      }

   if( ecc < 1.)
      while( fabs( delta_curr) > thresh)
         {
         if( n_iter++ > MAX_ITERATIONS)
            err = near_parabolic( curr, ecc) - mean_anom;
         else
            err = curr - ecc * sin( curr) - mean_anom;
         delta_curr = -err / (1. - ecc * cos( curr));
         curr += delta_curr;
         }
   else
      while( fabs( delta_curr) > thresh)
         {
         if( n_iter++ > MAX_ITERATIONS)
            err = -near_parabolic( curr, ecc) - mean_anom;
         else
            err = ecc * sinh( curr) - curr - mean_anom;
         delta_curr = -err / (ecc * cosh( curr) - 1.);
         curr += delta_curr;
         }
   return( is_negative ? offset - curr : offset + curr);
}