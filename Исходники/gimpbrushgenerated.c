/* set up lookup table */
static guchar *
gimp_brush_generated_calc_lut (gdouble radius,
                               gdouble hardness)
{
  guchar  *lookup;
  gint     length;
  gint     x;
  gdouble  d;
  gdouble  sum;
  gdouble  exponent;
  gdouble  buffer[OVERSAMPLING];

  length = OVERSAMPLING * ceil (1 + sqrt (2 * SQR (ceil (radius + 1.0))));

  lookup = g_malloc (length);
  sum = 0.0;

  if ((1.0 - hardness) < 0.0000004)
    exponent = 1000000.0;
  else
    exponent = 0.4 / (1.0 - hardness);

  for (x = 0; x < OVERSAMPLING; x++)
    {
      d = fabs ((x + 0.5) / OVERSAMPLING - 0.5);

      if (d > radius)
        buffer[x] = 0.0;
      else
        buffer[x] = gauss (pow (d / radius, exponent));

      sum += buffer[x];
    }

  for (x = 0; d < radius || sum > 0.00001; d += 1.0 / OVERSAMPLING)
    {
      sum -= buffer[x % OVERSAMPLING];

      if (d > radius)
        buffer[x % OVERSAMPLING] = 0.0;
      else
        buffer[x % OVERSAMPLING] = gauss (pow (d / radius, exponent));

      sum += buffer[x % OVERSAMPLING];
      lookup[x++] = RINT (sum * (255.0 / OVERSAMPLING));
    }

  while (x < length)
    {
      lookup[x++] = 0;
    }

  return lookup;
}