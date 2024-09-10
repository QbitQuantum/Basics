static void
draw_lights (gint startx,
	     gint starty,
	     gint pw,
	     gint ph)
{
  gdouble dxpos, dypos;
  gint    xpos, ypos;

  clear_light_marker ();

  gimp_vector_3d_to_2d (startx, starty, pw, ph,
			&dxpos, &dypos, &mapvals.viewpoint,
			&mapvals.lightsource.position);
  xpos = RINT (dxpos);
  ypos = RINT (dypos);

  if (xpos >= 0 && xpos <= PREVIEW_WIDTH &&
      ypos >= 0 && ypos <= PREVIEW_HEIGHT)
    draw_light_marker (xpos, ypos);
}