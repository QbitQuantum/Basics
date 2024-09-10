static void
focusblur_fft_buffer_update_depth_table (FblurFftBuffer *fft,
                                         gint            division,
                                         gint            slide)
{
  FblurFftDepthTable    *table;
  gfloat                 dfac, fval;
  gfloat                 r, f, c;
  gint                   ri, fi, ci;
  gint                   i;

  g_assert (division > 0);

  if (division == fft->depth.division &&
      slide    == fft->depth.slide)
    return;

  dfac = (gfloat) FBLUR_DEPTH_MAX / division;

  for (i = 0; i <= FBLUR_DEPTH_MAX; i ++)
    {
      table = &(fft->depth.table[i]);
      fval = (gfloat) (i - slide) / dfac;

      r = rintf (fval);

      ri = rintf (r * dfac) + slide;
      ri = CLAMP (ri, 0, FBLUR_DEPTH_MAX);

      table->round = ri;

      if (fabsf (r - fval) < 0.001f)
        {
          table->floor = table->ceil = ri;
          table->diff = 0.0f;
        }
      else
        {
          f = floorf (fval);
          c = ceilf (fval);

          fi = rintf (f * dfac) + slide;
          ci = rintf (c * dfac) + slide;

          fi = CLAMP (fi, 0, FBLUR_DEPTH_MAX);
          ci = CLAMP (ci, 0, FBLUR_DEPTH_MAX);

          table->floor = fi;
          table->ceil  = ci;

          table->diff  = (ci > fi) ? (gfloat) (i - fi) / (ci - fi) : 0.0f;
        }
    }

  fft->depth.division = division;
  fft->depth.slide = slide;
  fft->depth.count = 0;
}