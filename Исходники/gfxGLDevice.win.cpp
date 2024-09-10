void GFXGLDevice::enumerateAdapters( Vector<GFXAdapter*> &adapterList )
{
//   GL_ERROR_CHECK();
   WNDCLASS windowclass;
   dMemset( &windowclass, 0, sizeof( WNDCLASS ) );

   windowclass.lpszClassName = L"GFX-OpenGL";
   windowclass.style         = CS_OWNDC;
   windowclass.lpfnWndProc   = DefWindowProc;
   windowclass.hInstance     = winState.appInstance;

   if( !RegisterClass( &windowclass ) )
      AssertFatal( false, "Failed to register the window class for the GL test window." );

   // Now create a window
   HWND hwnd = CreateWindow( L"GFX-OpenGL", L"", WS_POPUP, 0, 0, 640, 480, 
                             NULL, NULL, winState.appInstance, NULL );
   AssertFatal( hwnd != NULL, "Failed to create the window for the GL test window." );

   // Create a device context
   HDC tempDC = GetDC( hwnd );
   AssertFatal( tempDC != NULL, "Failed to create device context" );

   // Create pixel format descriptor...
   PIXELFORMATDESCRIPTOR pfd;
   CreatePixelFormat( &pfd, 32, 0, 0, false );
   if( !SetPixelFormat( tempDC, ChoosePixelFormat( tempDC, &pfd ), &pfd ) )
      AssertFatal( false, "I don't know who's responcible for this, but I want caught..." );

   // Create a rendering context!
   HGLRC tempGLRC = wglCreateContext( tempDC );
   if( !wglMakeCurrent( tempDC, tempGLRC ) )
      AssertFatal( false, "I want them caught and killed." );

   // Add the GL renderer
   loadGLCore();
   loadGLExtensions(tempDC);

   GFXAdapter *toAdd = new GFXAdapter;
   toAdd->mIndex = 0;

   const char* renderer = (const char*) glGetString( GL_RENDERER );
   AssertFatal( renderer != NULL, "GL_RENDERER returned NULL!" );

   if (renderer)
   {
      dStrcpy(toAdd->mName, renderer);
      dStrncat(toAdd->mName, " OpenGL", GFXAdapter::MaxAdapterNameLen);
   }
   else
      dStrcpy(toAdd->mName, "OpenGL");

   toAdd->mType = OpenGL;
   toAdd->mShaderModel = 0.f;
   toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

   // Enumerate all available resolutions:
   DEVMODE devMode;
   U32 modeNum = 0;
   U32 stillGoing = true;
   while ( stillGoing )
   {
      dMemset( &devMode, 0, sizeof( devMode ) );
      devMode.dmSize = sizeof( devMode );

      stillGoing = EnumDisplaySettings( NULL, modeNum++, &devMode );

      if (( devMode.dmPelsWidth >= 480) && (devMode.dmPelsHeight >= 360 )
         && ( devMode.dmBitsPerPel == 16 || devMode.dmBitsPerPel == 32 )) 
      {
         GFXVideoMode vmAdd;

         vmAdd.bitDepth     = devMode.dmBitsPerPel;
         vmAdd.fullScreen   = true;
         vmAdd.refreshRate  = devMode.dmDisplayFrequency;
         vmAdd.resolution.x = devMode.dmPelsWidth;
         vmAdd.resolution.y = devMode.dmPelsHeight;

         // Only add this resolution if it is not already in the list:
         bool alreadyInList = false;
         for (Vector<GFXVideoMode>::iterator i = toAdd->mAvailableModes.begin(); i != toAdd->mAvailableModes.end(); i++)
         {
            if (vmAdd == *i)
            {
               alreadyInList = true;
               break;
            }
         }

         if(alreadyInList)
            continue;

         toAdd->mAvailableModes.push_back( vmAdd );
      }
   }

   // Add to the list of available adapters.
   adapterList.push_back(toAdd);

   // Cleanup our window
   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(tempGLRC);
   ReleaseDC(hwnd, tempDC);
   DestroyWindow(hwnd);
   UnregisterClass(L"GFX-OpenGL", winState.appInstance);
}