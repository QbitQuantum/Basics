static void
compute_preview_rectangle (gint * xp, gint * yp, gint * wid, gint * heig)
{
  gdouble x, y, w, h;

  if (width >= height)
    {
      w = (PREVIEW_WIDTH - 50.0);
      h = (gdouble) height *(w / (gdouble) width);

      x = (PREVIEW_WIDTH - w) / 2.0;
      y = (PREVIEW_HEIGHT - h) / 2.0;
    }
  else
    {
      h = (PREVIEW_HEIGHT - 50.0);
      w = (gdouble) width *(h / (gdouble) height);
      x = (PREVIEW_WIDTH - w) / 2.0;
      y = (PREVIEW_HEIGHT - h) / 2.0;
    }
  *xp = RINT (x);
  *yp = RINT (y);
  *wid = RINT (w);
  *heig = RINT (h);
}