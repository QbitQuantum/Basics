void CVideoReferenceClock::CleanupGLX()
{
  CLog::Log(LOGDEBUG, "CVideoReferenceClock: Cleaning up GLX");

  bool AtiWorkaround = false;
  const char* VendorPtr = (const char*)glGetString(GL_VENDOR);
  if (VendorPtr)
  {
    CStdString Vendor = VendorPtr;
    Vendor.ToLower();
    if (Vendor.compare(0, 3, "ati") == 0)
    {
      CLog::Log(LOGDEBUG, "CVideoReferenceClock: GL_VENDOR: %s, using ati dpy workaround", VendorPtr);
      AtiWorkaround = true;
    }
  }

  if (m_vInfo)
  {
    XFree(m_vInfo);
    m_vInfo = NULL;
  }
  if (m_Context)
  {
    glXMakeCurrent(m_Dpy, None, NULL);
    glXDestroyContext(m_Dpy, m_Context);
    m_Context = NULL;
  }
  if (m_Window)
  {
    XDestroyWindow(m_Dpy, m_Window);
    m_Window = 0;
  }

  //ati saves the Display* in their libGL, if we close it here, we crash
  if (m_Dpy && !AtiWorkaround)
  {
    XCloseDisplay(m_Dpy);
    m_Dpy = NULL;
  }
}