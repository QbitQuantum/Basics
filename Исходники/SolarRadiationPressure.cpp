      /* Determines if the satellite is in sunlight or shadow.
       * Taken from Montenbruck and Gill p. 80-83
       * @param r ECI position vector of spacecraft [m].
       * @param r_Sun Sun position vector (geocentric) [m].
       * @param r_Moon Moon position vector (geocentric) [m].
       * @return 0.0 if in shadow, 1.0 if in sunlight, 0 to 1.0 if in partial shadow
       */
   double SolarRadiationPressure::getShadowFunction(Vector<double> r, 
                                                    Vector<double> r_Sun,
                                                    Vector<double> r_Moon,
                                                    SolarRadiationPressure::ShadowModel sm)
   {
      // shadow function
      double v = 0.0;
      
      // Mean Radious of Sun, Moon and Earth
      const double R_sun = ASConstant::R_Sun;
      const double R_moon = ASConstant::R_Moon;
#pragma unused(R_moon)
      const double R_earth = ASConstant::R_Earth;

      Vector<double> e_Sun = r_Sun/norm(r_Sun);   // Sun direction unit vector

      double r_dot_sun = dot(r,e_Sun);
      
      if(r_dot_sun>0)
      {
         // Sunny side of central body is always fully lit and return
         v= 1.0;
         return v;
      }
      
      if(sm == SM_CYLINDRICAL)      
      {
         // Taken fram Jisheng Li P111, and checked with GMAT and Bernese5 SHADOW.f
         v = ((r_dot_sun>0 || norm(r-r_dot_sun*e_Sun)>R_earth) ? 1.0 : 0.0);
         return v;
      }
      else if(sm == SM_CONICAL)
      {
         /*
         // Taken from Montenbruck and Gill p. 80-83
         double s0, s2;
         
         // Montenbruck and Gill, eq. 3.79
         s0 = -dot(r,e_Sun); //-state[0]*unitsun[0] - state[1]*unitsun[1] - state[2]*unitsun[2];
         s2 = dot(r,r);      //state[0]*state[0] + state[1]*state[1] + state[2]*state[2];

         // Montenbruck and Gill, eq. 3.80
         double lsc = sqrt(s2 - s0*s0);

         // Montenbruck and Gill, eq. 3.81
         double sinf1 = (R_sun + R_earth) / norm(r_Sun);
         double sinf2 = (R_earth - R_earth) / norm(r_Sun);
         
         // Appropriate l1 and l2 temporarily
         double t1 = sinf1 * sinf1;
         double t2 = sinf2 * sinf2;
         double tanf1 = sqrt(t1 / (1.0 - t1));
         double tanf2 = sqrt(t2 / (1.0 - t2));
         
         // Montenbruck and Gill, eq. 3.82
         double c1 = s0 + R_earth / sinf1;
         double c2 = R_earth / sinf2 - s0;       // Different sign from M&G

         // Montenbruck and Gill, eq. 3.83
         double l1 = c1 * tanf1;
         double l2 = c2 * tanf2;

         if (lsc > l1)   // Outside of the penumbral cone
         {
            v = 1.0;
            return v;
         }
         else 
         {
            //lit = false;
            if (lsc < fabs(l2)) 
            {
               // Inside umbral cone
               if (c2 >= 0.0) 
               { 
                  // no annular ring
                  percentSun = 0.0;
                  dark = true;
               }
               else 
               {
                  // annular eclipse
                  pcbrad = asin(R_earth / sqrt(s2));
                  percentSun = (psunrad*psunrad - pcbrad*pcbrad) / 
                     (psunrad*psunrad);
                  dark = false;
               }

               return;
            }
            // In penumbra
            pcbrad = asin(R_earth / sqrt(s2));
            percentSun = ShadowFunction(state);
            lit = false;
            dark = false;
         }*/

         //////////////////////////////////////////////////////////////////////////

         double r_sun_mag = norm(r_Sun);
#pragma unused(r_sun_mag)
         double r_mag = norm(r);
         
         Vector<double> d = r_Sun-r;            // vector from sc to sun
         double dmag = norm(d);               

         double a = std::asin(R_sun/dmag);               // eq. 3.85
         double b = std::asin(R_earth/r_mag);               // eq. 3.86
         double c = std::acos(-1.0*dot(r,d)/(r_mag*dmag));   // eq. 3.87

         if((a+b)<=c)         // in Sun light
         {
            v = 1.0;
         }
         else if(c < (b-a))      // in Umbra
         {
            v =  0.0;
         }
         else               // in Penumbra 
         {
            double x = (c*c+a*a-b*b)/(2*c);                     // eq. 3.93
            double y = std::sqrt(a*a-x*x);
            double A = a*a*std::acos(x/a)+b*b*std::acos((c-x)/b)-c*y;         // eq. 3.92
            v = 1.0 - A/(ASConstant::PI*a*a);                  // eq. 3.94
         }

         return v;
      }
      else
      {
         // unexpected value
         Exception e("Unexpect ShadowModel in getShadowFunction()");
         GPSTK_THROW(e);
      }

      return v;

   }  // End of method 'SolarRadiationPressure::getShadowFunction()'