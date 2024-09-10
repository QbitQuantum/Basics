static guchar*
rgb_to_hsl (GimpDrawable     *drawable,
            LICEffectChannel  effect_channel)
{
  guchar       *themap, data[4];
  gint          x, y;
  GimpRGB       color;
  GimpHSL       color_hsl;
  gdouble       val = 0.0;
  glong         maxc, index = 0;
  GimpPixelRgn  region;
  GRand        *gr;

  gr = g_rand_new ();

  maxc = drawable->width * drawable->height;

  gimp_pixel_rgn_init (&region, drawable, border_x, border_y,
                       border_w, border_h, FALSE, FALSE);

  themap = g_new (guchar, maxc);

  for (y = 0; y < region.h; y++)
    {
      for (x = 0; x < region.w; x++)
        {
          data[3] = 255;

          gimp_pixel_rgn_get_pixel (&region, data, x, y);
          gimp_rgba_set_uchar (&color, data[0], data[1], data[2], data[3]);
          gimp_rgb_to_hsl (&color, &color_hsl);

          switch (effect_channel)
            {
            case LIC_HUE:
              val = color_hsl.h * 255;
              break;
            case LIC_SATURATION:
              val = color_hsl.s * 255;
              break;
            case LIC_BRIGHTNESS:
              val = color_hsl.l * 255;
              break;
            }

          /* add some random to avoid unstructured areas. */
          val += g_rand_double_range (gr, -1.0, 1.0);

          themap[index++] = (guchar) CLAMP0255 (RINT (val));
        }
    }

  g_rand_free (gr);

  return themap;
}