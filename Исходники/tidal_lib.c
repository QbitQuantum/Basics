/* Assumes mvir in Msun and dt in Myr. */
inline float halo_tidal_range(float mvir, float av_a) {
  /* TIDAL_FORCE_LIMIT = Gc*m/r^3 (km/s/Myr per comoving Mpc) */
  /* r^3 = Gc*m/TIDAL_FORCE_LIMIT / a^2 */
  /* Mutiply by 2 to be safe.*/
  float tforce_limit = TIDAL_FORCE_LIMIT;
  if (tidal_extra_range && TIDAL_FORCE_LIMIT > 0.001) {
    tforce_limit = 0.01 * TIDAL_FORCE_LIMIT;
    if (tforce_limit < 0.001) tforce_limit = 0.001;
  }
  return (2*cbrtf(fabs(mvir*Gc/(tforce_limit*av_a*av_a))));
}