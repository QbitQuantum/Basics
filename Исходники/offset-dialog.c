static void
offset_response (GtkWidget    *widget,
                 gint          response_id,
                 OffsetDialog *dialog)
{
  if (response_id == GTK_RESPONSE_OK)
    {
      GimpImage *image = dialog->image;

      if (image)
        {
          GimpDrawable *drawable = gimp_image_get_active_drawable (image);
          gint          offset_x;
          gint          offset_y;

          offset_x =
            RINT (gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (dialog->off_se),
                                              0));
          offset_y =
            RINT (gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (dialog->off_se),
                                              1));

          gimp_drawable_offset (drawable,
                                dialog->context,
                                dialog->fill_type & WRAP_AROUND ? TRUE : FALSE,
                                dialog->fill_type & FILL_MASK,
                                offset_x, offset_y);
          gimp_image_flush (image);
        }
    }

  gtk_widget_destroy (dialog->dialog);
}