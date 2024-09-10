static void
d_paint_spiral (GfigObject *obj)
{
  /* first point center */
  /* Next point is radius */
  gdouble    *line_pnts;
  gint        seg_count = 0;
  gint        i = 0;
  DobjPoints *center_pnt;
  DobjPoints *radius_pnt;
  gint16      shift_x;
  gint16      shift_y;
  gdouble     ang_grid;
  gdouble     ang_loop;
  gdouble     radius;
  gdouble     offset_angle;
  gdouble     sp_cons;
  gint        loop;
  GdkPoint    last_pnt = { 0, 0 };
  gint        clock_wise = 1;

  g_assert (obj != NULL);

  center_pnt = obj->points;

  if (!center_pnt || !center_pnt->next)
    return; /* no-line */

  /* Go around all the points drawing a line from one to the next */

  radius_pnt = center_pnt->next; /* this defines the vetices */

  /* Have center and radius - get lines */
  shift_x = radius_pnt->pnt.x - center_pnt->pnt.x;
  shift_y = radius_pnt->pnt.y - center_pnt->pnt.y;

  radius = sqrt ((shift_x * shift_x) + (shift_y * shift_y));

  clock_wise = obj->type_data / abs (obj->type_data);

  offset_angle = atan2 (shift_y, shift_x);

  if (offset_angle < 0)
    offset_angle += 2.0 * G_PI;

  sp_cons = radius/(obj->type_data * 2.0 * G_PI + offset_angle);
  /* Lines */
  ang_grid = 2.0 * G_PI / 180.0;

  /* count - */
  seg_count = abs (obj->type_data * 180.0) + clock_wise * (gint)RINT (offset_angle/ang_grid);

  line_pnts = g_new0 (gdouble, 2 * seg_count + 3);

  for (loop = 0 ; loop <= seg_count; loop++)
    {
      gdouble  lx, ly;
      GdkPoint calc_pnt;

      ang_loop = (gdouble)loop * ang_grid;

      lx = sp_cons * ang_loop * cos (ang_loop)*clock_wise;
      ly = sp_cons * ang_loop * sin (ang_loop);

      calc_pnt.x = RINT (lx + center_pnt->pnt.x);
      calc_pnt.y = RINT (ly + center_pnt->pnt.y);

      /* Miss out duped pnts */
      if (!loop)
        {
          if (calc_pnt.x == last_pnt.x && calc_pnt.y == last_pnt.y)
            {
              continue;
            }
        }

      line_pnts[i++] = calc_pnt.x;
      line_pnts[i++] = calc_pnt.y;
      last_pnt = calc_pnt;
    }

  /* Scale before drawing */
  if (selvals.scaletoimage)
    scale_to_original_xy (&line_pnts[0], i / 2);
  else
    scale_to_xy (&line_pnts[0], i / 2);

  /* One go */
  if (obj->style.paint_type == PAINT_BRUSH_TYPE)
    {
      gfig_paint (selvals.brshtype,
                  gfig_context->drawable_id,
                  i, line_pnts);
    }

  g_free (line_pnts);
}