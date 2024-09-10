int cylindrical_equidistant (mapx_class *current,
			     double lat, double lon, double *x, double *y)
{
  double dlon;
  double phi, lam;
  
  dlon = lon - current->lon0;
  NORMALIZE(dlon);
  
  phi = RADIANS (lat);
  lam = RADIANS (dlon);
  
  *x =  current->Rg * lam * current->cos_phi1;
  *y =  current->Rg * phi;
  
  *x += current->false_easting;
  *y += current->false_northing;
  
  return 0;
}