static gfloat
posterize_lut_func (gint   *ilevels,
                    gint    n_channels,
                    gint    channel,
                    gfloat  value)
{
  gint levels;

  /* don't posterize the alpha channel */
  if ((n_channels == 2 || n_channels == 4) && channel == n_channels -1)
    return value;

  if (*ilevels < 2)
    levels = 2;
  else
    levels = *ilevels;

  value = RINT (value * (levels - 1.0)) / (levels - 1.0);

  return value;
}