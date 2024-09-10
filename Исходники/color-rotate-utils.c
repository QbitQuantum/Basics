ReducedImage*
rcm_reduce_image (GimpDrawable *drawable,
		  GimpDrawable *mask,
		  gint          LongerSize,
		  gint          Slctn)
{
  guint32       image;
  GimpPixelRgn  srcPR, srcMask;
  ReducedImage *temp;
  guchar       *tempRGB, *src_row, *tempmask, *src_mask_row;
  gint          i, j, x1, x2, y1, y2;
  gint          RH, RW, width, height, bytes;
  gboolean      NoSelectionMade;
  gint          offx, offy;
  gdouble      *tempHSV, H, S, V;

  bytes = drawable->bpp;
  temp = g_new0 (ReducedImage, 1);

  /* get bounds of image or selection */

  gimp_drawable_mask_bounds (drawable->drawable_id, &x1, &y1, &x2, &y2);

  if (((x2-x1) != drawable->width) || ((y2-y1) != drawable->height))
    NoSelectionMade = FALSE;
  else
    NoSelectionMade = TRUE;

  switch (Slctn)
    {
    case ENTIRE_IMAGE:
      x1 = 0;
      x2 = drawable->width;
      y1 = 0;
      y2 = drawable->height;
      break;

    case SELECTION_IN_CONTEXT:
      x1 = MAX (0, x1 - (x2-x1) / 2.0);
      x2 = MIN (drawable->width, x2 + (x2-x1) / 2.0);
      y1 = MAX (0, y1 - (y2-y1) / 2.0);
      y2 = MIN (drawable->height, y2 + (y2-y1) / 2.0);
      break;

    default:
      break; /* take selection dimensions */
    }

  /* clamp to image size since this is the size of the mask */

  gimp_drawable_offsets (drawable->drawable_id, &offx, &offy);
  image = gimp_item_get_image (drawable->drawable_id);

  x1 = CLAMP (x1, - offx, gimp_image_width (image) - offx);
  x2 = CLAMP (x2, - offx, gimp_image_width (image) - offx);
  y1 = CLAMP (y1, - offy, gimp_image_height (image) - offy);
  y2 = CLAMP (y2, - offy, gimp_image_height (image) - offy);

  /* calculate size of preview */

  width  = x2 - x1;
  height = y2 - y1;

  if (width < 1 || height < 1)
    return temp;

  if (width > height)
    {
      RW = LongerSize;
      RH = (float) height * (float) LongerSize / (float) width;
    }
  else
    {
      RH = LongerSize;
      RW = (float)width * (float) LongerSize / (float) height;
    }

  /* allocate memory */

  tempRGB  = g_new (guchar, RW * RH * bytes);
  tempHSV  = g_new (gdouble, RW * RH * bytes);
  tempmask = g_new (guchar, RW * RH);

  gimp_pixel_rgn_init (&srcPR, drawable, x1, y1, width, height, FALSE, FALSE);
  gimp_pixel_rgn_init (&srcMask, mask,
                       x1 + offx, y1 + offy, width, height, FALSE, FALSE);

  src_row = g_new (guchar, width * bytes);
  src_mask_row = g_new (guchar, width * bytes);

  /* reduce image */

  for (i = 0; i < RH; i++)
    {
      gint whichcol, whichrow;

      whichrow = (float)i * (float)height / (float)RH;
      gimp_pixel_rgn_get_row (&srcPR, src_row, x1, y1 + whichrow, width);
      gimp_pixel_rgn_get_row (&srcMask, src_mask_row,
                              x1 + offx, y1 + offy + whichrow, width);

      for (j = 0; j < RW; j++)
        {
          whichcol = (float)j * (float)width / (float)RW;

          if (NoSelectionMade)
            tempmask[i*RW+j] = 255;
          else
            tempmask[i*RW+j] = src_mask_row[whichcol];

          gimp_rgb_to_hsv4 (&src_row[whichcol*bytes], &H, &S, &V);

          tempRGB[i*RW*bytes+j*bytes+0] = src_row[whichcol*bytes+0];
          tempRGB[i*RW*bytes+j*bytes+1] = src_row[whichcol*bytes+1];
          tempRGB[i*RW*bytes+j*bytes+2] = src_row[whichcol*bytes+2];

          tempHSV[i*RW*bytes+j*bytes+0] = H;
          tempHSV[i*RW*bytes+j*bytes+1] = S;
          tempHSV[i*RW*bytes+j*bytes+2] = V;

          if (bytes == 4)
            tempRGB[i*RW*bytes+j*bytes+3] = src_row[whichcol*bytes+3];
        }
    }

  /* return values */

  temp->width  = RW;
  temp->height = RH;
  temp->rgb    = tempRGB;
  temp->hsv    = tempHSV;
  temp->mask   = tempmask;

  return temp;
}