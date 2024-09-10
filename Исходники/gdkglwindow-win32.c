static void
_gdk_win32_gl_window_impl_wait_gdk (GdkGLWindow *glwindow)
{
  g_return_if_fail (GDK_IS_WIN32_GL_WINDOW (glwindow));

  GdiFlush ();

  /* Get DC. */
  GDK_GL_WINDOW_IMPL_WIN32_HDC_GET (GDK_GL_WINDOW_IMPL_WIN32 (glwindow->impl));
}