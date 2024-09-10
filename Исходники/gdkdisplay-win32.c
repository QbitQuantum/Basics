void
gdk_win32_display_check_composited (GdkWin32Display *display)
{
  gboolean composited;

  /* On Windows 8 and later, DWM (composition) is always enabled */
  if (g_win32_check_windows_version (6, 2, 0, G_WIN32_OS_ANY))
    {
      composited = TRUE;
    }
  else
    {
      if (DwmIsCompositionEnabled (&composited) != S_OK)
        composited = FALSE;
    }

  gdk_display_set_composited (GDK_DISPLAY (display), composited);
}