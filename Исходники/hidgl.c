void
hidgl_draw_line (int cap, Coord width, Coord x1, Coord y1, Coord x2, Coord y2, double scale)
{
  double angle;
  float deltax, deltay, length;
  float wdx, wdy;
  int circular_caps = 0;
  int hairline = 0;

  if (width == 0.0)
    hairline = 1;

  if (width < scale)
    width = scale;

  deltax = x2 - x1;
  deltay = y2 - y1;

  length = sqrt (deltax * deltax + deltay * deltay);

  if (length == 0) {
    /* Assume the orientation of the line is horizontal */
    angle = 0;
    wdx = -width / 2.;
    wdy = 0;
    length = 1.;
    deltax = 1.;
    deltay = 0.;
  } else {
    wdy = deltax * width / 2. / length;
    wdx = -deltay * width / 2. / length;

    if (deltay == 0.)
      angle = (deltax < 0) ? 270. : 90.;
    else
      angle = 180. / M_PI * atanl (deltax / deltay);

    if (deltay < 0)
      angle += 180.;
  }

  switch (cap) {
    case Trace_Cap:
    case Round_Cap:
      circular_caps = 1;
      break;

    case Square_Cap:
    case Beveled_Cap:
      x1 -= deltax * width / 2. / length;
      y1 -= deltay * width / 2. / length;
      x2 += deltax * width / 2. / length;
      y2 += deltay * width / 2. / length;
      break;
  }

  hidgl_ensure_triangle_space (&buffer, 2);
  hidgl_add_triangle (&buffer, x1 - wdx, y1 - wdy,
                               x2 - wdx, y2 - wdy,
                               x2 + wdx, y2 + wdy);
  hidgl_add_triangle (&buffer, x1 - wdx, y1 - wdy,
                               x2 + wdx, y2 + wdy,
                               x1 + wdx, y1 + wdy);

  /* Don't bother capping hairlines */
  if (circular_caps && !hairline)
    {
      draw_cap (width, x1, y1, angle, scale);
      draw_cap (width, x2, y2, angle + 180., scale);
    }
}