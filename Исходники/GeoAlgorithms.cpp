bool GeoAlgorithms::initVincenty(double aLat1, double aLon1, double aLat2, double aLon2)
{

   // Verify that input latitudes are between -90 and 90 and longitudes are
   // between -180 and 180
   if ((abs(aLat1) > 90) || (abs(aLat2) > 90) || (abs(aLon1) > 180)
        || (abs(aLon2) > 180))
   {
       return false;
   }

   // convert inputs in degrees to radians:
   aLat1 = aLat1 * 0.0174532925199433;
   aLon1 = aLon1 * 0.0174532925199433;
   aLat2 = aLat2 * 0.0174532925199433;
   aLon2 = aLon2 * 0.0174532925199433;

   // correct for errors at exact poles by adjusting 0.6 millimeters:
   if (abs(GeoConversions::PI_OVER_2-abs(aLat1)) < (1e-10))
   {
       aLat1 = getSign(aLat1) * (GeoConversions::PI_OVER_2 - (1e-10));
   }
   if (abs(GeoConversions::PI_OVER_2-abs(aLat2)) < (1e-10))
   {
       aLat2 = getSign(aLat2) * (GeoConversions::PI_OVER_2 - (1e-10));
   }

   // Ellipse CalcuaAltitudeions?
   mVincentyU1 = atan(m1MinF*tan(aLat1));
   mVincentyU2 = atan(m1MinF*tan(aLat2));
   aLon1 = getMod(aLon1, (GeoConversions::TWO_PI));
   aLon2 = getMod(aLon2, (GeoConversions::TWO_PI));
   mVincentyL = aLon2-aLon1;
   if (abs(mVincentyL) > PI)
   {
     mVincentyL = getSign(mVincentyL) * (GeoConversions::TWO_PI - abs(mVincentyL));
   }

   // Initialize Variables for Loop
   double sin_mVincentyU1 = sin(mVincentyU1);
   double cos_mVincentyU1 = cos(mVincentyU1);
   double sin_mVincentyU2 = sin(mVincentyU2);
   double cos_mVincentyU2 = cos(mVincentyU2);
   double sinU1_sinU2 = sin_mVincentyU1 * sin_mVincentyU2;
   double cosU1_sinU2 = cos_mVincentyU1 * sin_mVincentyU2;
   double sinU1_cosU2 = sin_mVincentyU1 * cos_mVincentyU2;
   double cosU1_cosU2 = cos_mVincentyU1 * cos_mVincentyU2;
   double sin_mVincentyLambda = 0;
   double cos_mVincentyLambda = 0;
   double cos_mVincentyAlpha = 0;
   double sin_mVincentySigma = 0;
   double cos_mVincentySigma = 0;
   double lLambdaOld = 0;
   long   lIterCount = 0;
   double lSinSigma = 0;
   double lCosSigma = 0;
   double c = 0;
   mVincentySigma = 0;
   mVincentyAlpha = 0;
   mVincentyCosToSigmaM = 0;
   mVincentyLambda = mVincentyL;

   // ?
   while ((!lIterCount) || abs((mVincentyLambda-lLambdaOld) > (1e-12)))
   {
      lIterCount += 1;
      if (lIterCount > 50)
      {
          mVincentyLambda = PI;
          break;
      }

      sin_mVincentyLambda = sin(mVincentyLambda);
      cos_mVincentyLambda = cos(mVincentyLambda);
      lLambdaOld = mVincentyLambda;
      lSinSigma = sqrt(pow(cos_mVincentyU2 * sin_mVincentyLambda, 2) +
         pow(cosU1_sinU2 - sinU1_cosU2 * cos_mVincentyLambda, 2));
      lCosSigma = sinU1_sinU2 + cosU1_cosU2 * cos_mVincentyLambda;
      mVincentySigma = atan2(lSinSigma, lCosSigma);
      sin_mVincentySigma = sin(mVincentySigma);
      cos_mVincentySigma = cos(mVincentySigma);
      mVincentyAlpha = asin(cosU1_cosU2 * sin_mVincentyLambda / sin_mVincentySigma);
      cos_mVincentyAlpha = cos(mVincentyAlpha);
      mVincentyCosToSigmaM = cos_mVincentySigma -  2 * sinU1_sinU2 / pow(cos_mVincentyAlpha, 2);
      c = mF/ 16 * pow(cos_mVincentyAlpha, 2) * (4 + mF * (4 - 3 * pow(cos_mVincentyAlpha, 2)));
      mVincentyLambda = mVincentyL + (1 - c) * mF * sin(mVincentyAlpha) * (mVincentySigma + c * sin_mVincentySigma *
         (mVincentyCosToSigmaM + c * cos_mVincentySigma * (-1 + 2 * pow(mVincentyCosToSigmaM, 2))));

      // Correct for convergence failure in the case of essentially
      // antipodal points
      if (mVincentyLambda > PI)
      {
          mVincentyLambda = PI;
          break;
      }
   }

   return true;
}