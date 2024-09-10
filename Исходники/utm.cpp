void geographic_to_tm_sphere(double R, double k0, 
			     double lon_mer, double FN, double FE,
			     double lat_rad, double lon_rad,
			     double* N, double* E)
{
  double Rk0 = R*k0;
  double B = cos(lat_rad) * sin(lon_rad - lon_mer);
  *E = FE + Rk0*atanh(B);
  *N = FN + Rk0*atan(tan(lat_rad)/cos(lon_rad - lon_mer));
}