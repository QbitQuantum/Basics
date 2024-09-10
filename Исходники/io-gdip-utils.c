static gboolean
gdip_save_bitmap_to_callback (GpBitmap *bitmap,
                              const CLSID *format,
                              const EncoderParameters *encoder_params,
                              GdkPixbufSaveFunc save_func,
                              gpointer user_data,
                              GError **error)
{
  HRESULT hr;  
  IStream *streamOut = NULL;
  gboolean success = FALSE;
  guint64 zero = 0;
  GpStatus status;

  hr = CreateStreamOnHGlobal (NULL, TRUE, &streamOut);
  if (!SUCCEEDED (hr)) {
    gdip_set_error_from_hresult (error, GDK_PIXBUF_ERROR_FAILED, hr, _("Could not create stream: %s"));
    return FALSE;
  }

  status = GdipSaveImageToStream ((GpImage *)bitmap, streamOut, format, encoder_params);
  if (Ok != status) {
    gdip_set_error_from_gpstatus (error, GDK_PIXBUF_ERROR_FAILED, status);
    IStream_Release (streamOut);
    return FALSE;
  }

  /* seek back to the beginning of the stream */
  hr = IStream_Seek (streamOut, *(LARGE_INTEGER *)&zero, STREAM_SEEK_SET, NULL);
  if (!SUCCEEDED (hr)) {
    gdip_set_error_from_hresult (error, GDK_PIXBUF_ERROR_FAILED, hr, _("Could not seek stream: %s"));
    IStream_Release (streamOut);
    return FALSE;
  }
  
  for (;;) {
    char buffer[LOAD_BUFFER_SIZE];
    ULONG nread;
    
    hr = IStream_Read (streamOut, buffer, sizeof(buffer), &nread);
    if (!SUCCEEDED (hr))
      {
        gdip_set_error_from_hresult (error, GDK_PIXBUF_ERROR_FAILED, hr, _("Could not read from stream: %s"));
        break;
      }
    else if (0 == nread) {
      success = TRUE; /* EOF */
      break;
    }
    else if (!(*save_func) (buffer, nread, error, user_data))
      break;
  }
  
  IStream_Release (streamOut);
  
  return success;
}                     