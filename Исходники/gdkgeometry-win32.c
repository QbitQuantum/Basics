gboolean
_gdk_windowing_window_queue_antiexpose (GdkWindow *window,
					GdkRegion *area)
{
  HRGN hrgn = _gdk_win32_gdkregion_to_hrgn (area, 0, 0);

  GDK_NOTE (EVENTS, g_print ("_gdk_windowing_window_queue_antiexpose: ValidateRgn %p %s\n",
			     GDK_WINDOW_HWND (window),
			     _gdk_win32_gdkregion_to_string (area)));

  ValidateRgn (GDK_WINDOW_HWND (window), hrgn);

  DeleteObject (hrgn);

  return FALSE;
}