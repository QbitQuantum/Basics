double Track_Elsasser2007::getRadialIntegral(const double r_min,
                                             const double r_max) const
{
   if( r_min < 0. || r_max < r_min )
   {
      cerr << "double Track_Elsasser2007::getRadialIntegral(const double, const double) const -- Invalid r_min, r_max specified." << endl;
      exit(1);
   }

   if( r_max == r_min )
      return 0.;

   cerr << "Warning: implementation of double Track_Elsasser2007::getRadialIntegral(const double, const double) const not complete." << endl;

//    double r_end = (r_max < r_penumbra ? r_max : r_penumbra);
//    double dose = 0.;
//    if( r_min < r_core )
//    {
//       if( r_max <= r_core )
//          dose += dose_core * (r_max*r_max - r_min*r_min);
//       else
//       {
//          dose += dose_core * (r_core*r_core - r_min*r_min);
// 
// 
//          dose += 2 * k_p * log(r_end / r_core);
//       }
//    }
//    else if( r_min < r_penumbra )
//    {
//       dose += 2 * k_p * log(r_end / r_min);
//    }
// 
//    return dose / (r_max*r_max - r_min*r_min);
   return -1.;
}