//------------------------------------------------------------------------------
//--------------------------------------
// Object proper...
//--------------------------------------
//
Surface* 
Surface::create(HWND        io_clientWnd,
                const Int32 in_width,
                const Int32 in_height)
{
   // Must return a new OpenGL::Surface* of resolution closest to in_w/h.
   //  Should also activate the device.
   //
   AssertFatal(io_clientWnd != NULL, "No client window handle");

   Surface* pRetSurf = new Surface;

#ifndef DEBUG
   BOOL   test    = TRUE;
   bool   found   = false;
   UInt32 modeNum = 0;
   DEVMODE devMode;

   while (test == TRUE) {
      memset(&devMode, 0, sizeof(devMode));
      devMode.dmSize = sizeof(devMode);
      test = EnumDisplaySettings(NULL, modeNum, &devMode);
      if (devMode.dmPelsWidth        == (UInt32)in_width  &&
          devMode.dmPelsHeight       == (UInt32)in_height) {
         found = true;
      }

      modeNum++;
   }

   if (found == false) {
      delete pRetSurf;
      return NULL;
   }

   // Change the window position
   AssertMessage(false, avar("Changing window style (%d, %d)", in_width, in_height));
   GetWindowRect(io_clientWnd, &pRetSurf->m_oldWindowRect);
   LONG style = GetWindowLong(io_clientWnd, GWL_STYLE);
   style &= ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME);
   SetWindowLong(io_clientWnd, GWL_STYLE, style);

   LONG exStyle = GetWindowLong(io_clientWnd, GWL_EXSTYLE);
   exStyle |= WS_EX_TOPMOST;
   SetWindowLong(io_clientWnd, GWL_EXSTYLE, exStyle);
   BOOL posSuccess = SetWindowPos(io_clientWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
   AssertFatal(posSuccess == TRUE, "Error setting pos");

   // Annnnd, set the new display mode.  Desktop icons?
   //
   memset(&devMode, 0, sizeof(devMode));
   devMode.dmSize = sizeof(devMode);
   devMode.dmPelsWidth  = in_width;
   devMode.dmPelsHeight = in_height;
   devMode.dmFields = DM_PELSWIDTH  |
                      DM_PELSHEIGHT;

#if 1
   AssertMessage(false, avar("Changing display settings: (%d, %d)", devMode.dmPelsWidth, devMode.dmPelsHeight));
   ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
   VidModeChecker::sm_theInstance.changedDisplaySettings();
#endif

   SetForegroundWindow(io_clientWnd);
   posSuccess = SetWindowPos(io_clientWnd, HWND_TOPMOST, 0, 0, in_width, in_height, SWP_FRAMECHANGED);
   AssertFatal(posSuccess == TRUE, "Error setting pos");
   pRetSurf->m_windowStyleChanged = true;
#endif

   pRetSurf->m_hWnd = io_clientWnd;
   pRetSurf->m_hDC = GetDC(pRetSurf->m_hWnd);
   if (pRetSurf->m_hDC == NULL) {
      AssertWarn(0, "Unable to get a DC for the window");
      delete pRetSurf;
      return NULL;
   }

   // Set the Pixel format, first retrieving the old format
   //
   pRetSurf->m_oldPixelFormat = GetPixelFormat(pRetSurf->m_hDC);
   DescribePixelFormat(pRetSurf->m_hDC, pRetSurf->m_oldPixelFormat,
                       sizeof(PIXELFORMATDESCRIPTOR),
                       &pRetSurf->m_oldPixelFormatDescriptor);

   int chosenPixelFormat;
   PIXELFORMATDESCRIPTOR chosenPFD;
   if (pRetSurf->choosePixelFormat(chosenPixelFormat,
                                   chosenPFD,
                                   pRetSurf->m_hWnd,
                                   pRetSurf->m_hDC) == false) {
      AssertWarn(0, "Unable to choose a pixel format");
      delete pRetSurf;
      return NULL;
   }

   BOOL spSuccess = SetPixelFormat(pRetSurf->m_hDC,
                                   chosenPixelFormat,
                                   &chosenPFD);
   if (spSuccess != TRUE) {
      AssertWarn(0, "Unable to set the pixel format");
      delete pRetSurf;
      return NULL;
   }

   // Create the HGLRC
   //
   pRetSurf->m_hGLRC = wglCreateContext(pRetSurf->m_hDC);
   if (pRetSurf->m_hGLRC == NULL) {
      AssertWarn(0, "Unable to create a GL Render context");
      delete pRetSurf;
      return NULL;
   }

   BOOL mcSuccess = wglMakeCurrent(pRetSurf->m_hDC, pRetSurf->m_hGLRC);
   if (mcSuccess != TRUE) {
      AssertWarn(0, "Unable to make the GL Render context current");
      delete pRetSurf;
      return NULL;
   }
   pRetSurf->m_glrcMadeCurrent = true;

   // Retreive the strings associated with this driver, they are useful
   //  for debugging and such...
   //
   const char* pVendor     = (const char*)glGetString(GL_VENDOR);
   const char* pRenderer   = (const char*)glGetString(GL_RENDERER);
   const char* pVersion    = (const char*)glGetString(GL_VERSION);
   const char* pExtensions = (const char*)glGetString(GL_EXTENSIONS);

   if (pVendor != NULL) {
      pRetSurf->m_pVendorString = new char[strlen(pVendor) + 1];
      strcpy(pRetSurf->m_pVendorString, pVendor);
   }
   if (pRenderer != NULL) {
      pRetSurf->m_pRendererString = new char[strlen(pRenderer) + 1];
      strcpy(pRetSurf->m_pRendererString, pRenderer);
   }
   if (pVersion != NULL) {
      pRetSurf->m_pVersionString = new char[strlen(pVersion) + 1];
      strcpy(pRetSurf->m_pVersionString, pVersion);
   }
   if (pExtensions != NULL) {
      pRetSurf->m_pExtensionsString = new char[strlen(pExtensions) + 1];
      strcpy(pRetSurf->m_pExtensionsString, pExtensions);
   }

   // Allocate our vertex arrays...
   //
   pRetSurf->m_pVertexArray    = new DGLVertex4F[sm_maxNumVertices];
   pRetSurf->m_pColorArray     = new DGLColor4F[sm_maxNumVertices];
   pRetSurf->m_pTexCoord0Array = new DGLTexCoord4F[sm_maxNumVertices];
   pRetSurf->m_pHazeStoreArray = new DGLHazeCoordF[sm_maxNumVertices];

   pRetSurf->surfaceWidth  = in_width;
   pRetSurf->surfaceHeight = in_height;

   // Create the texture/handle cache...
   //
   pRetSurf->m_pTextureCache = new TextureCache(pRetSurf);
   pRetSurf->m_pHandleCache  = new HandleCache(2048, 2153);

   // Set up our default state...
   //
   pRetSurf->setFillMode(GFX_FILL_CONSTANT);
   pRetSurf->setFillColor(&ColorF(0, 0, 0));
   pRetSurf->setAlphaSource(GFX_ALPHA_NONE);
   pRetSurf->setShadeSource(GFX_SHADE_NONE);
   pRetSurf->setHazeSource(GFX_HAZE_NONE);
   pRetSurf->setTextureWrap(true);
   pRetSurf->setTransparency(false);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   // We're ready to go...
   //
   return pRetSurf;
}