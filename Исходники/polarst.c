long Convert_Polar_Stereographic_To_Geodetic (double Easting,
                                              double Northing,
                                              double *Latitude,
                                              double *Longitude)

{ /*  BEGIN Convert_Polar_Stereographic_To_Geodetic  */
/*
 *  The function Convert_Polar_Stereographic_To_Geodetic converts Polar
 *  Stereographic coordinates (easting and northing) to geodetic
 *  coordinates (latitude and longitude) according to the current ellipsoid
 *  and Polar Stereographic projection Parameters. If any errors occur, the
 *  code(s) are returned by the function, otherwise POLAR_NO_ERROR
 *  is returned.
 *
 *  Easting          : Easting (X), in meters                   (input)
 *  Northing         : Northing (Y), in meters                  (input)
 *  Latitude         : Latitude, in radians                     (output)
 *  Longitude        : Longitude, in radians                    (output)
 *
 */

  double dy = 0, dx = 0;
  double rho = 0;
  double t;
  double PHI, sin_PHI;
  double tempPHI = 0.0;
  double essin;
  double pow_es;
  double delta_radius;
  long Error_Code = POLAR_NO_ERROR;
  double min_easting = Polar_False_Easting - Polar_Delta_Easting;
  double max_easting = Polar_False_Easting + Polar_Delta_Easting;
  double min_northing = Polar_False_Northing - Polar_Delta_Northing;
  double max_northing = Polar_False_Northing + Polar_Delta_Northing;

  if (Easting > max_easting || Easting < min_easting)
  { /* Easting out of range */
    Error_Code |= POLAR_EASTING_ERROR;
  }
  if (Northing > max_northing || Northing < min_northing)
  { /* Northing out of range */
    Error_Code |= POLAR_NORTHING_ERROR;
  }

  if (!Error_Code)
  {
    dy = Northing - Polar_False_Northing;
    dx = Easting - Polar_False_Easting;

    /* Radius of point with origin of false easting, false northing */
    rho = sqrt(dx * dx + dy * dy);   
    
    delta_radius = sqrt(Polar_Delta_Easting * Polar_Delta_Easting + Polar_Delta_Northing * Polar_Delta_Northing);

    if(rho > delta_radius)
    { /* Point is outside of projection area */
      Error_Code |= POLAR_RADIUS_ERROR;
    }

    if (!Error_Code)
    { /* no errors */
      if ((dy == 0.0) && (dx == 0.0))
      {
        *Latitude = PI_OVER_2;
        *Longitude = Polar_Origin_Long;

      }
      else
      {
        if (Southern_Hemisphere != 0)
        {
          dy *= -1.0;
          dx *= -1.0;
        }

        if (fabs(fabs(Polar_Origin_Lat) - PI_OVER_2) > 1.0e-10)
          t = rho * tc / (Polar_a_mc);
        else
          t = rho * e4 / (two_Polar_a);
        PHI = PI_OVER_2 - 2.0 * atan(t);
        while (fabs(PHI - tempPHI) > 1.0e-10)
        {
          tempPHI = PHI;
          sin_PHI = sin(PHI);
          essin =  es * sin_PHI;
          pow_es = POLAR_POW(essin);
          PHI = PI_OVER_2 - 2.0 * atan(t * pow_es);
        }
        *Latitude = PHI;
        *Longitude = Polar_Origin_Long + atan2(dx, -dy);

        if (*Longitude > PI)
          *Longitude -= TWO_PI;
        else if (*Longitude < -PI)
          *Longitude += TWO_PI;


        if (*Latitude > PI_OVER_2)  /* force distorted values to 90, -90 degrees */
          *Latitude = PI_OVER_2;
        else if (*Latitude < -PI_OVER_2)
          *Latitude = -PI_OVER_2;

        if (*Longitude > PI)  /* force distorted values to 180, -180 degrees */
          *Longitude = PI;
        else if (*Longitude < -PI)
          *Longitude = -PI;

      }
      if (Southern_Hemisphere != 0)
      {
        *Latitude *= -1.0;
        *Longitude *= -1.0;
      }
    }
  }
  return (Error_Code);
} /* END OF Convert_Polar_Stereographic_To_Geodetic */