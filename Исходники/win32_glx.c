GLXContext
glXCreateContext(Display * display, XVisualInfo * visinfo,
  GLXContext share, Bool direct)
{
  /* KLUDGE: GLX really expects a display pointer to be passed
     in as the first parameter, but Win32 needs an HDC instead,
     so BE SURE that the global XHDC is set before calling this
     routine. */
  HGLRC context;

  context = wglCreateContext(XHDC);

#if 0
  /* XXX GLUT doesn't support it now, so don't worry about display list
     and texture object sharing. */
  if (share) {
    wglShareLists(share, context);
  }
#endif

  /* Since direct rendering is implicit, the direct flag is
     ignored. */

  return context;
}