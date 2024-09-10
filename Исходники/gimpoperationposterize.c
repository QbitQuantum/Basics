static gboolean
gimp_operation_posterize_process (GeglOperation       *operation,
                                  void                *in_buf,
                                  void                *out_buf,
                                  glong                samples,
                                  const GeglRectangle *roi,
                                  gint                 level)
{
  GimpOperationPosterize *posterize = GIMP_OPERATION_POSTERIZE (operation);
  gfloat                 *src       = in_buf;
  gfloat                 *dest      = out_buf;
  gfloat                  levels;

  levels = posterize->levels - 1.0;

  while (samples--)
    {
      dest[RED]   = RINT (src[RED]   * levels) / levels;
      dest[GREEN] = RINT (src[GREEN] * levels) / levels;
      dest[BLUE]  = RINT (src[BLUE]  * levels) / levels;
      dest[ALPHA] = RINT (src[ALPHA] * levels) / levels;

      src  += 4;
      dest += 4;
    }

  return TRUE;
}