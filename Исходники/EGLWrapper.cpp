bool CEGLWrapper::InitDisplay(EGLDisplay *display)
{
  if (!display || !m_nativeTypes)
    return false;

  //nativeDisplay can be (and usually is) NULL. Don't use if(nativeDisplay) as a test!
  EGLint status;
  EGLNativeDisplayType *nativeDisplay = NULL;
  if (!m_nativeTypes->GetNativeDisplay((XBNativeDisplayType**)&nativeDisplay))
    return false;

  *display = eglGetDisplay(*nativeDisplay);
  CheckError();
  if (*display == EGL_NO_DISPLAY)
  {
    CLog::Log(LOGERROR, "EGL failed to obtain display");
    return false;
  }

  status = eglInitialize(*display, 0, 0);
  CheckError();
  return status;
}