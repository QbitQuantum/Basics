static gboolean
gst_gdiscreencapsrc_screen_capture (GstGDIScreenCapSrc * src, GstBuffer * buf)
{
  HWND capture;
  HDC winDC;
  gint height, width;
  GstMapInfo map;

  if (G_UNLIKELY (!src->hBitmap || !src->dibMem))
    return FALSE;

  width = src->info.bmiHeader.biWidth;
  height = -src->info.bmiHeader.biHeight;

  /* Capture screen */
  capture = GetDesktopWindow ();
  winDC = GetWindowDC (capture);

  BitBlt (src->memDC, 0, 0, width, height,
      winDC, src->src_rect.left, src->src_rect.top, SRCCOPY);

  ReleaseDC (capture, winDC);

  /* Capture mouse cursor */
  if (src->show_cursor) {
    CURSORINFO ci;

    ci.cbSize = sizeof (CURSORINFO);
    GetCursorInfo (&ci);
    if (ci.flags & CURSOR_SHOWING) {
      ICONINFO ii;

      GetIconInfo (ci.hCursor, &ii);

      DrawIconEx (src->memDC,
          ci.ptScreenPos.x - src->src_rect.left - ii.xHotspot,
          ci.ptScreenPos.y - src->src_rect.top - ii.yHotspot, ci.hCursor, 0, 0,
          0, NULL, DI_DEFAULTSIZE | DI_NORMAL | DI_COMPAT);

      DeleteObject (ii.hbmColor);
      DeleteObject (ii.hbmMask);
    }
  }

  /* Copy DC bits to GST buffer */
  gst_buffer_map (buf, &map, GST_MAP_WRITE);
  memcpy (map.data, src->dibMem, map.size);
  gst_buffer_unmap (buf, &map);

  return TRUE;
}