static void
gimp_curve_calculate (GimpCurve *curve)
{
  gint *points;
  gint  i;
  gint  num_pts;
  gint  p1, p2, p3, p4;

  if (gimp_data_is_frozen (GIMP_DATA (curve)))
    return;

  points = g_newa (gint, curve->n_points);

  switch (curve->curve_type)
    {
    case GIMP_CURVE_SMOOTH:
      /*  cycle through the curves  */
      num_pts = 0;
      for (i = 0; i < curve->n_points; i++)
        if (curve->points[i].x >= 0.0)
          points[num_pts++] = i;

      /*  Initialize boundary curve points */
      if (num_pts != 0)
        {
          GimpVector2 point;
          gint        boundary;

          point    = curve->points[points[0]];
          boundary = ROUND (point.x * (gdouble) (curve->n_samples - 1));

          for (i = 0; i < boundary; i++)
            curve->samples[i] = point.y;

          point    = curve->points[points[num_pts - 1]];
          boundary = ROUND (point.x * (gdouble) (curve->n_samples - 1));

          for (i = boundary; i < curve->n_samples; i++)
            curve->samples[i] = point.y;
        }

      for (i = 0; i < num_pts - 1; i++)
        {
          p1 = points[MAX (i - 1, 0)];
          p2 = points[i];
          p3 = points[i + 1];
          p4 = points[MIN (i + 2, num_pts - 1)];

          gimp_curve_plot (curve, p1, p2, p3, p4);
        }

      /* ensure that the control points are used exactly */
      for (i = 0; i < num_pts; i++)
        {
          gdouble x = curve->points[points[i]].x;
          gdouble y = curve->points[points[i]].y;

          curve->samples[ROUND (x * (gdouble) (curve->n_samples - 1))] = y;
        }

      g_object_notify (G_OBJECT (curve), "samples");
      break;

    case GIMP_CURVE_FREE:
      break;
    }
}