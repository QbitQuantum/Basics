static void
gdk_gl_pixmap_impl_win32_wait_gdk (GdkGLDrawable *gldrawable)
{
  GdiFlush ();

  /* Sync. */
  gdk_gl_pixmap_sync_gdk (GDK_GL_PIXMAP (gldrawable));
}