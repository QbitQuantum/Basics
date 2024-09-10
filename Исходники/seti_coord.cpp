void            co_XyzToEq(double xyz[], double *ra, double *dec)
  {
  double r,rho,x,y,z;
  x = xyz[0];
  y = xyz[1];
  z = xyz[2];
  rho = sqrt(x * x + y * y);
  r = sqrt(rho * rho + z * z);
  if (r < 1.0e-20)
    {
    *ra = 0.0;
    *dec = 0.0;
    }
  else
    {
    *ra = Atan2 (y,x) * 12.0 / M_PI;
    if (fabs(rho) > fabs(z))
      *dec = atan(z/rho) * 180.0 / M_PI;
    else
      {
      if (z > 0.0)
        *dec = 90.0 - atan(rho/z) * 180.0 / M_PI;
      else
        *dec = -90.0 - atan(rho/z) * 180.0 / M_PI;
      }
    }
  }