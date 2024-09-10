static gboolean process (GeglOperation       *operation,
                         void                *in_buf,
                         void                *out_buf,
                         glong                samples,
                         const GeglRectangle *roi,
                         gint                 level)
{
  GeglProperties *o      = GEGL_PROPERTIES (operation);
  gfloat     *src    = in_buf;
  gfloat     *dest   = out_buf;
  gfloat      levels = o->levels;

  while (samples--)
    {
      gint i;
      for (i=0; i < 3; i++)
        dest[i] = RINT (src[i]   * levels) / levels;
      dest[3] = src[3];

      src  += 4;
      dest += 4;
    }

  return TRUE;
}