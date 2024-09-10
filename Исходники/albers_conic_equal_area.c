int inverse_albers_conic_equal_area(mapx_class *current, double x, double y, 
				    double *lat, double *lon)
{
  double phi, lam, rho, rmy, theta, chi;

  x -= current->false_easting;
  y -= current->false_northing;

  rmy = current->rho0 - y;
  rho = sqrt(x*x + rmy*rmy);
  theta = current->n >= 0 ?
    atan2( x,  rmy) :
    atan2(-x, -rmy);

  chi = rho*current->n/current->Rg;
  phi = asin((current->C - chi*chi)/(2*current->n));
  lam = theta/current->n;

  *lat = DEGREES(phi);
  *lon = DEGREES(lam) + current->lon0;
  NORMALIZE(*lon);
  
  return 0;
}