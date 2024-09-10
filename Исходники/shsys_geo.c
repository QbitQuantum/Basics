/**
 * Calculate the distance between two geodetic location in miles.
 */
double shgeo_dist(shgeo_t *f_geo, shgeo_t *t_geo)
{
  static const shnum_t mile_mod = 90.9;
  shnum_t theta, dist;
  shnum_t lat1, lat2;
  shnum_t lon1, lon2;

  shgeo_loc(f_geo, &lat1, &lon1, NULL);
  shgeo_loc(t_geo, &lat2, &lon2, NULL);

  theta = lon1 - lon2;
  dist = (sinl(_deg2rad(lat1)) * sinl(_deg2rad(lat2))) + 
    (cosl(_deg2rad(lat1)) * cosl(_deg2rad(lat2)) * cosl(_deg2rad(theta)));
  dist = acosl(dist);
  dist = _rad2deg(dist);
  dist = dist * mile_mod;

  return ((double)dist);
}