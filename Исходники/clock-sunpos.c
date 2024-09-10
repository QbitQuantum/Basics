/* Calculate the position of the sun at a given time.  pages 89-91 */
void
sun_position (time_t unix_time, gdouble *lat, gdouble *lon)
{
  gdouble jd, D, N, M, E, x, v, lambda;
  gdouble ra, dec;
  jd = unix_time_to_julian_date (unix_time);

  /* Calculate number of days since the epoch */
  D = jd - EPOCH;

  N = D*360/365.242191;

  /* normalize to 0 - 360 degrees */
  NORMALIZE (N);

  /* Step 4: */
  M = N + EPSILON_G - MU_G;
  NORMALIZE (M);

  /* Step 5: convert to radians */
  M = DEG_TO_RADS (M);

  /* Step 6: */
  E = solve_keplers_equation (ECCENTRICITY, M);

  /* Step 7: */
  x = sqrt ((1 + ECCENTRICITY)/(1 - ECCENTRICITY)) * tan (E/2);

  /* Step 8, 9 */
  v = 2 * RADS_TO_DEG (atan (x));
  NORMALIZE (v);

  /* Step 10 */
  lambda = v + MU_G;
  NORMALIZE (lambda);

  /* convert the ecliptic longitude to right ascension and declination */
  ecliptic_to_equatorial (DEG_TO_RADS (lambda), 0.0, &ra, &dec);

  ra = ra - (G_PI/12) * greenwich_sidereal_time (unix_time);
  ra = RADS_TO_DEG (ra);
  dec = RADS_TO_DEG (dec);
  NORMALIZE (ra);
  NORMALIZE (dec);

  *lat = dec;
  *lon = ra;
}