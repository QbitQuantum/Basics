int Game_Init(void *parms = NULL, int num_parms = 0)
{
   // this is called once after the initial window is created and
   // before the main event loop is entered, do all your initialization
   // here
   
   // create IDirectDraw interface 7.0 object and test for error
   if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
      return(0);
   
   // set cooperation to full screen
   if (FAILED(lpdd->SetCooperativeLevel(main_window_handle, 
                                         DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | 
                                         DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
      return(0);
   
   // set display mode to 640x480x8
   if (FAILED(lpdd->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,0,0)))
      return(0);
   

   // clear ddsd and set size
   DDRAW_INIT_STRUCT(ddsd); 
   
   // enable valid fields
   ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
   
   // set the backbuffer count field to 1, use 2 for triple buffering
   ddsd.dwBackBufferCount = 1;
   
   // request a complex, flippable
   ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
   
   // create the primary surface
   if (FAILED(lpdd->CreateSurface(&ddsd, &lpddsprimary, NULL)))
      return(0);
   
   // now query for attached surface from the primary surface
   
   // this line is needed by the call
   ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
   
   // get the attached back buffer surface
   if (FAILED(lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps, &lpddsback)))
     return(0);
   
   // build up the palette data array
   for (int color=1; color < 255; color++)
   {
      // fill with random RGB values
      palette[color].peRed   = 0;
      palette[color].peGreen = 0;
      palette[color].peBlue  = color;
      
      // set flags field to PC_NOCOLLAPSE
      palette[color].peFlags = PC_NOCOLLAPSE;
   } // end for color

   // now fill in entry 0 and 255 with black and white
   palette[0].peRed     = 0;
   palette[0].peGreen   = 0;
   palette[0].peBlue    = 0;
   palette[0].peFlags   = PC_NOCOLLAPSE;
   
   palette[255].peRed   = 255;
   palette[255].peGreen = 255;
   palette[255].peBlue  = 255;
   palette[255].peFlags = PC_NOCOLLAPSE;
   
   // create the palette object
   if (FAILED(lpdd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256 | 
                                   DDPCAPS_INITIALIZE, 
                                   palette,&lpddpal, NULL)))
   {
      return(0);
   }

   // finally attach the palette to the primary surface
   if (FAILED(lpddsprimary->SetPalette(lpddpal)))
      return(0);

   // return success or failure or your own return code here
   return(1);

} // end Game_Init