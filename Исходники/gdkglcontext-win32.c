/*< private >*/
GdkGLContextImpl *
_gdk_win32_gl_context_impl_new (GdkGLContext  *glcontext,
                                GdkGLDrawable *gldrawable,
                                GdkGLContext  *share_list,
                                gboolean       direct,
                                int            render_type)
{
  GdkGLConfig *glconfig;
  HDC hdc;
  HGLRC hglrc;
  GdkGLContextImplWin32 *share_impl = NULL;

  GDK_GL_NOTE_FUNC_PRIVATE ();

  /*
   * Create an OpenGL rendering context.
   */

  glconfig = gdk_gl_drawable_get_gl_config (gldrawable);

  /* Get DC. */
  hdc = gdk_win32_gl_window_get_hdc (GDK_GL_WINDOW (gldrawable));
  if (hdc == NULL)
    return NULL;

  GDK_GL_NOTE_FUNC_IMPL ("wglCreateContext");

  hglrc = wglCreateContext (hdc);

  /* Release DC. */
  gdk_win32_gl_window_release_hdc (GDK_GL_WINDOW (gldrawable));

  if (hglrc == NULL)
    return NULL;

  if (share_list != NULL && GDK_IS_GL_CONTEXT (share_list))
    {
      GDK_GL_NOTE_FUNC_IMPL ("wglShareLists");

      share_impl = GDK_GL_CONTEXT_IMPL_WIN32 (share_list);
      if (!wglShareLists (share_impl->hglrc, hglrc))
        {
          wglDeleteContext (hglrc);
          return NULL;
        }
    }

  /*
   * Instantiate the GdkGLContextImplWin32 object.
   */

  return gdk_win32_gl_context_impl_new_common (glcontext,
                                               glconfig,
                                               share_list,
                                               render_type,
                                               hglrc,
                                               FALSE);
}