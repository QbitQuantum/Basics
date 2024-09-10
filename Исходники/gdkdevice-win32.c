GdkWindow *
_gdk_device_win32_window_at_position (GdkDevice       *device,
                                      gdouble         *win_x,
                                      gdouble         *win_y,
                                      GdkModifierType *mask,
                                      gboolean         get_toplevel)
{
  GdkWindow *window = NULL;
  POINT screen_pt, client_pt;
  HWND hwnd, hwndc;
  RECT rect;

  GetCursorPos (&screen_pt);

  if (get_toplevel)
    {
      /* Only consider visible children of the desktop to avoid the various
       * non-visible windows you often find on a running Windows box. These
       * might overlap our windows and cause our walk to fail. As we assume
       * WindowFromPoint() can find our windows, we follow similar logic
       * here, and ignore invisible and disabled windows.
       */
      hwnd = GetDesktopWindow ();
      do {
        window = gdk_win32_handle_table_lookup (hwnd);

        if (window != NULL &&
            GDK_WINDOW_TYPE (window) != GDK_WINDOW_ROOT &&
            GDK_WINDOW_TYPE (window) != GDK_WINDOW_FOREIGN)
          break;

        screen_to_client (hwnd, screen_pt, &client_pt);
        hwndc = ChildWindowFromPointEx (hwnd, client_pt, CWP_SKIPDISABLED  |
                                                         CWP_SKIPINVISIBLE);

	/* Verify that we're really inside the client area of the window */
	if (hwndc != hwnd)
	  {
	    GetClientRect (hwndc, &rect);
	    screen_to_client (hwndc, screen_pt, &client_pt);
	    if (!PtInRect (&rect, client_pt))
	      hwndc = hwnd;
	  }

      } while (hwndc != hwnd && (hwnd = hwndc, 1));

    }
  else
    {
      hwnd = WindowFromPoint (screen_pt);

      /* Verify that we're really inside the client area of the window */
      GetClientRect (hwnd, &rect);
      screen_to_client (hwnd, screen_pt, &client_pt);
      if (!PtInRect (&rect, client_pt))
	hwnd = NULL;

      /* If we didn't hit any window at that point, return the desktop */
      if (hwnd == NULL)
        {
          if (win_x)
            *win_x = screen_pt.x + _gdk_offset_x;
          if (win_y)
            *win_y = screen_pt.y + _gdk_offset_y;

          return gdk_get_default_root_window ();
        }

      window = gdk_win32_handle_table_lookup (hwnd);
    }

  if (window && (win_x || win_y))
    {
      if (win_x)
        *win_x = client_pt.x;
      if (win_y)
        *win_y = client_pt.y;
    }

  return window;
}