GimpTempBuf *
gimp_drawable_get_sub_preview (GimpDrawable *drawable,
                               gint          src_x,
                               gint          src_y,
                               gint          src_width,
                               gint          src_height,
                               gint          dest_width,
                               gint          dest_height)
{
  GimpItem    *item;
  GimpImage   *image;
  GeglBuffer  *buffer;
  GimpTempBuf *preview;
  gdouble      scale;
  gint         scaled_x;
  gint         scaled_y;

  g_return_val_if_fail (GIMP_IS_DRAWABLE (drawable), NULL);
  g_return_val_if_fail (src_x >= 0, NULL);
  g_return_val_if_fail (src_y >= 0, NULL);
  g_return_val_if_fail (src_width  > 0, NULL);
  g_return_val_if_fail (src_height > 0, NULL);
  g_return_val_if_fail (dest_width  > 0, NULL);
  g_return_val_if_fail (dest_height > 0, NULL);

  item = GIMP_ITEM (drawable);

  g_return_val_if_fail ((src_x + src_width)  <= gimp_item_get_width  (item), NULL);
  g_return_val_if_fail ((src_y + src_height) <= gimp_item_get_height (item), NULL);

  image = gimp_item_get_image (item);

  if (! image->gimp->config->layer_previews)
    return NULL;

  buffer = gimp_drawable_get_buffer (drawable);

  preview = gimp_temp_buf_new (dest_width, dest_height,
                               gimp_drawable_get_preview_format (drawable));

  scale = MIN ((gdouble) dest_width  / (gdouble) src_width,
               (gdouble) dest_height / (gdouble) src_height);

  scaled_x = RINT ((gdouble) src_x * scale);
  scaled_y = RINT ((gdouble) src_y * scale);

  gegl_buffer_get (buffer,
                   GEGL_RECTANGLE (scaled_x, scaled_y, dest_width, dest_height),
                   scale,
                   gimp_temp_buf_get_format (preview),
                   gimp_temp_buf_get_data (preview),
                   GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_CLAMP);

  return preview;
}