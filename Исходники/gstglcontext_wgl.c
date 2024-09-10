static gboolean
gst_gl_context_wgl_create_context (GstGLContext * context,
    GstGLAPI gl_api, GstGLContext * other_context, GError ** error)
{
  GstGLWindow *window;
  GstGLContextWGL *context_wgl;
  GstGLContextWGL *other_wgl = NULL;
  HDC device;

  context_wgl = GST_GL_CONTEXT_WGL (context);
  window = gst_gl_context_get_window (context);
  device = (HDC) gst_gl_window_get_display (window);

  if (other_context) {
    if (!GST_GL_IS_CONTEXT_WGL (other_context)) {
      g_set_error (error, GST_GL_CONTEXT_ERROR,
          GST_GL_CONTEXT_ERROR_WRONG_CONFIG,
          "Cannot share context with a non-WGL context");
      goto failure;
    }
    other_wgl = (GstGLContextWGL *) other_context;
  }

  context_wgl->wgl_context = wglCreateContext (device);
  if (context_wgl->wgl_context)
    GST_DEBUG ("gl context created: %" G_GUINTPTR_FORMAT,
        (guintptr) context_wgl->wgl_context);
  else {
    g_set_error (error, GST_GL_CONTEXT_ERROR,
        GST_GL_CONTEXT_ERROR_CREATE_CONTEXT, "failed to create glcontext:0x%x",
        (unsigned int) GetLastError ());
    goto failure;
  }
  g_assert (context_wgl->wgl_context);

  GST_LOG ("gl context id: %" G_GUINTPTR_FORMAT,
      (guintptr) context_wgl->wgl_context);

  if (other_wgl) {
    if (!wglShareLists (other_wgl->wgl_context, context_wgl->wgl_context)) {
      g_set_error (error, GST_GL_CONTEXT_ERROR,
          GST_GL_CONTEXT_ERROR_CREATE_CONTEXT, "failed to share contexts 0x%x",
          (unsigned int) GetLastError ());
      goto failure;
    }
  }

  gst_object_unref (window);

  return TRUE;

failure:
  gst_object_unref (window);

  return FALSE;
}