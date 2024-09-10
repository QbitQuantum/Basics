void XYZ2GEOM(double X, double Y, double Z, double *Lon, double *Lat)
{
    *Lon = asin(Z / sqrt(X * X + Y * Y + Z * Z)) * 180 / M_PI;
    *Lat = atan2(Y, X) * 180 / M_PI;
}