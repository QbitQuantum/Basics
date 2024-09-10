   OGLDriver::OGLDriver(HWND hWnd, float viewportWidth, float viewportHeight, bool fullscreen)
   {
      m_hWnd = hWnd;
      m_viewPortWidth = viewportWidth;
      m_viewPortHeight = viewportHeight;
      m_fullscreen = fullscreen;

      CreateContext();
   }