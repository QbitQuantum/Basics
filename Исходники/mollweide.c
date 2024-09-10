int mollweide(mapx_class *current, double lat, double lon,
	      double *x, double *y)
{
  double dlon;
  double phi, lam, theta, delta;
  double sin_theta, cos_theta, psi, epsilon=1e-6;
  int it, maxit=10;
  
  dlon = lon - current->lon0;
  NORMALIZE(dlon);
  
  phi = RADIANS (lat);
  lam = RADIANS (dlon);
  
  delta = 0.0;
  theta = phi;
  sin_theta = sin(theta);
  cos_theta = cos(theta);
  if (fabs(cos_theta) > epsilon)
  { psi = PI*sin(phi);
    it = 0;
    repeat
    { delta = -(theta + sin_theta - psi) / (1 + cos_theta);
      theta += delta;
      sin_theta = sin(theta);
      cos_theta = cos(theta);
      if (++it >= maxit) break;
    } until (fabs(delta) <= epsilon);
    theta /= 2.0;
    sin_theta = sin(theta);
    cos_theta = cos(theta);
  }