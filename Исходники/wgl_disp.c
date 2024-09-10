static HGLRC init_ogl_context_ex(HDC dc, bool fc, int major, int minor)
{
   HWND testwnd = NULL;
   HDC testdc   = NULL;
   HGLRC testrc = NULL;
   HGLRC old_rc = NULL;
   HDC old_dc   = NULL;
   HGLRC glrc   = NULL;

   testwnd = _al_win_create_hidden_window();
   if (!testwnd)
      return NULL;

   old_rc = wglGetCurrentContext();
   old_dc = wglGetCurrentDC();

   testdc = GetDC(testwnd);
   testrc = init_temp_context(testwnd);
   if (!testrc)
      goto bail;

   if (is_wgl_extension_supported("WGL_ARB_create_context", testdc)) {
      int attrib[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, major,
                      WGL_CONTEXT_MINOR_VERSION_ARB, minor,
                      WGL_CONTEXT_FLAGS_ARB, 0,
                      0};
      if (fc)
         attrib[5] = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
      if (!init_context_creation_extensions())
         goto bail;
      /* TODO: we could use the context sharing feature */
      glrc = _wglCreateContextAttribsARB(dc, 0, attrib);
   }
   else
      goto bail;

bail:
   wglMakeCurrent(NULL, NULL);
   if (testrc) {
      wglDeleteContext(testrc);
   }

   wglMakeCurrent(old_dc, old_rc);

   _wglCreateContextAttribsARB = NULL;

   if (testwnd) {
      ReleaseDC(testwnd, testdc);
      DestroyWindow(testwnd);
   }

   return glrc;
}