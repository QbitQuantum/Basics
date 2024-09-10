int InitDirectDraw()
{
   DDSURFACEDESC2 ddsd;
   DDSCAPS2       ddscaps;
   HRESULT		  hRet;

   // Create the main DirectDraw object.
   hRet = DirectDrawCreateEx(NULL, (VOID**)&g_pDD, IID_IDirectDraw7, NULL);
   if( hRet != DD_OK )
       return -1;

   // Get exclusive mode.
   hRet = g_pDD->SetCooperativeLevel(g_hMainWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
   if( hRet != DD_OK )
       return -2;

   // Set the video mode to 640x480x16.
   hRet = g_pDD->SetDisplayMode(640, 480, 16, 0, 0);
   if( hRet != DD_OK )
       return -3;

   // Prepare to create the primary surface by initializing
   // the fields of a DDSURFACEDESC2 structure.
   ZeroMemory(&ddsd, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);
   ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
   ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
      DDSCAPS_COMPLEX;
   ddsd.dwBackBufferCount = 1;

   // Create the primary surface.
   hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSFront, NULL);
   if( hRet != DD_OK )
       return -1;

   // Get a pointer to the back buffer.
   ZeroMemory(&ddscaps, sizeof(ddscaps));
   ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
   hRet = g_pDDSFront->GetAttachedSurface(&ddscaps, &g_pDDSBack);
   if( hRet != DD_OK )
       return -1;

   return 0;

} 