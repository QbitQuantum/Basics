static void
wave (guchar  *src,
      guchar  *dst,
      gint     width,
      gint     height,
      gint     bypp,
      gboolean has_alpha,
      gdouble  cen_x,
      gdouble  cen_y,
      gdouble  amplitude,
      gdouble  wavelength,
      gdouble  phase,
      gboolean smear,
      gboolean reflective,
      gboolean verbose)
{
  glong   rowsiz;
  guchar *p;
  guchar *dest;
  gint    x1, y1, x2, y2;
  gint    x, y;
  gint    prog_interval = 0;
  gint    x1_in, y1_in, x2_in, y2_in;

  gdouble xhsiz, yhsiz;       /* Half size of selection */
  gdouble radius, radius2;    /* Radius and radius^2 */
  gdouble amnt, d;
  gdouble needx, needy;
  gdouble dx, dy;
  gdouble xscale, yscale;

  gint xi, yi;

  guchar *values[4];
  guchar  zeroes[4] = { 0, 0, 0, 0 };

  phase  = phase * G_PI / 180.0;
  rowsiz = width * bypp;

  if (verbose)
    {
      gimp_progress_init (_("Waving"));
      prog_interval = height / 10;
    }

  x1 = y1 = 0;
  x2 = width;
  y2 = height;

  /* Compute wave radii (semiaxes) */
  xhsiz = (double) (x2 - x1) / 2.0;
  yhsiz = (double) (y2 - y1) / 2.0;

  /* These are the necessary scaling factors to turn the wave
     ellipse into a large circle */

  if (xhsiz < yhsiz)
    {
      xscale = yhsiz / xhsiz;
      yscale = 1.0;
    }
  else if (xhsiz > yhsiz)
    {
      xscale = 1.0;
      yscale = xhsiz / yhsiz;
    }
  else
    {
      xscale = 1.0;
      yscale = 1.0;
    }

  radius  = MAX (xhsiz, yhsiz);
  radius2 = radius * radius;

  /* Wave the image! */

  dst += y1 * rowsiz + x1 * bypp;

  wavelength *= 2;

  for (y = y1; y < y2; y++)
    {
      dest = dst;

      if (verbose && (y % prog_interval == 0))
        gimp_progress_update ((double) y / (double) height);

      for (x = x1; x < x2; x++)
        {
          /* Distance from current point to wave center, scaled */
          dx = (x - cen_x) * xscale;
          dy = (y - cen_y) * yscale;

          /* Distance^2 to center of *circle* (our scaled ellipse) */
          d = sqrt (dx * dx + dy * dy);

          /* Use the formula described above. */

          /* Calculate waved point and scale again to ellipsify */

          /*
           * Reflective waves are strange - the effect is much
           * more like a mirror which is in the shape of
           * the wave than anything else.
           */

          if (reflective)
            {
              amnt = amplitude * fabs (sin (((d / wavelength) * (2.0 * G_PI) +
                                             phase)));

              needx = (amnt * dx) / xscale + cen_x;
              needy = (amnt * dy) / yscale + cen_y;
            }
          else
            {
              amnt = amplitude * sin (((d / wavelength) * (2.0 * G_PI) +
                                       phase));

              needx = (amnt + dx) / xscale + cen_x;
              needy = (amnt + dy) / yscale + cen_y;
            }

          /* Calculations complete; now copy the proper pixel */

          if (smear)
            {
              xi = CLAMP (needx, 0, width - 2);
              yi = CLAMP (needy, 0, height - 2);
            }
          else
            {
              xi = needx;
              yi = needy;
            }

          p = src + rowsiz * yi + xi * bypp;

          x1_in = WITHIN (0, xi, width - 1);
          y1_in = WITHIN (0, yi, height - 1);
          x2_in = WITHIN (0, xi + 1, width - 1);
          y2_in = WITHIN (0, yi + 1, height - 1);

          if (x1_in && y1_in)
            values[0] = p;
          else
            values[0] = zeroes;

          if (x2_in && y1_in)
            values[1] = p + bypp;
          else
            values[1] = zeroes;

          if (x1_in && y2_in)
            values[2] = p + rowsiz;
          else
            values[2] = zeroes;

          if (x2_in && y2_in)
            values[3] = p + bypp + rowsiz;
          else
            values[3] = zeroes;

          gimp_bilinear_pixels_8 (dest, needx, needy, bypp, has_alpha, values);
          dest += bypp;
        }

      dst += rowsiz;
    }

  if (verbose)
    gimp_progress_update (1.0);
}