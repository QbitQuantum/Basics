bool PlayerRenderer::init()
{
#ifdef Q_OS_WIN32
  // Request Multimedia Class Schedule Service.
  DwmEnableMMCSS(TRUE);
#endif

  // Signals presence of MPGetNativeDisplay().
  const char *extensions = "GL_MP_MPGetNativeDisplay";
  return mpv_opengl_cb_init_gl(m_mpvGL, extensions, get_proc_address, NULL) >= 0;
}