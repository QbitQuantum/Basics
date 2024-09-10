static void prepareSwapOnDC(HDC hdc,HDC &oldDC,HGLRC &oldRC)
{
  oldDC = wglGetCurrentDC();
  oldRC = wglGetCurrentContext();

  if(oldDC != hdc)
  {
    HGLRC rc = rcFromDC[hdc];
    if(rc)
      Mine_wglMakeCurrent(hdc,rc);
    else
      printLog("video/opengl: SwapBuffers called on DC with no active rendering context. This is potentially bad.\n");
  }
}