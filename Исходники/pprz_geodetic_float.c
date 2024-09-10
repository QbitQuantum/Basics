/* Convert utm to lla (float).
 * Note this conversion is not very accurate. If high accuracy needed use lla_of_utm_d.
 * @param[out] lla position in rad, alt is copied directly from utm
 * @param[in]  utm position in m, alt in m
 */
void lla_of_utm_f(struct LlaCoor_f *lla, struct UtmCoor_f *utm)
{
  float scale = 1 / N / serie_coeff_proj_mercator[0];
  float real = (utm->north - DELTA_NORTH) * scale;
  float img = (utm->east - DELTA_EAST) * scale;
  struct complex z = { real, img };

  int8_t k;
  for (k = 1; k < 2; k++) {
    struct complex z_ = { real, img };
    CScal(2.*k, z_);
    CSin(z_);
    CScal(serie_coeff_proj_mercator_inverse[k], z_);
    CSub(z_, z);
  }

  float lambda_c = LambdaOfUtmZone(utm->zone);
  lla->lon = lambda_c + atanf(sinhf(z.im) / cosf(z.re));
  float phi_ = asinf(sinf(z.re) / coshf(z.im));
  float il = isometric_latitude_fast_f(phi_);
  lla->lat = inverse_isometric_latitude_f(il, E, 1e-8);

  // copy alt above reference ellipsoid
  lla->alt = utm->alt;
}