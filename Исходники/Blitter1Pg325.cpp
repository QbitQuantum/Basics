int Game_Init(void *parms = NULL, int num_parms = 0)
{
   // this is called once after the initial window is created and
   // before the main event loop is entered, do all your initialization
   // here
   int retval = 0;
   colors16 = new WORD[65536];

   // create IDirectDraw interface 7.0 object and test for error
   if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
   {

      // something bad happened during initialization, buh-bye!
      SendMessage(main_window_handle,WM_CLOSE,0,0);   
      g_ddStepFailure = DDSF_DDACCESS;

      retval = 0;
   }
   else
   {
      // set cooperation to normal since this will be a windowed app
      lpdd->SetCooperativeLevel( main_window_handle, 
                                    DDSCL_FULLSCREEN
                                 |  DDSCL_ALLOWMODEX
                                 |  DDSCL_EXCLUSIVE
                                 |  DDSCL_ALLOWREBOOT
                                 |  DDSCL_MULTITHREADED      );
                                 
      if (FAILED(lpdd->SetDisplayMode( screen_width,
                                       screen_height,
                                       screen_bpp,
                                       0,                // refresh rate (use default)
                                       0              )  // flags..
                )
         )           
      {
         SendMessage(main_window_handle,WM_CLOSE,0,0);   
         g_ddStepFailure = DDSF_SETDISPLAYMODE;
         retval = 0;
      }
      else
      {

         {
            // create direct draw surface..
            memset(&ddsd,0,sizeof(ddsd));
            ddsd.dwSize = sizeof(ddsd);
            ddsd.dwFlags = DDSD_CAPS;
            ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
            if (FAILED(lpdd->CreateSurface(&ddsd,
                                           &lpddsprimary,
                                           NULL) 
                      )
               )
            {
               SendMessage(main_window_handle,WM_CLOSE,0,0);   
               g_ddStepFailure = DDSF_SURFACECREATE;
               retval = 0;
            }
            else
            {
            
               {
                  // now get the pixel format..
                  //
                  
                  memset(&ddpixel,0,sizeof(ddpixel));
                  
                  ddpixel.dwSize = sizeof(ddpixel);
                  
                  lpddsprimary->GetPixelFormat(&ddpixel);
                  
                  if (ddpixel.dwFlags & DDPF_RGB)
                  {
                     // RGB mode..
                     switch(ddpixel.dwRGBBitCount)
                     {
                        case 15:
                           {
                              // 5.5.5
                              g_rgb16bitmode = RGB16MODE_555;
                              makeColors555();
                              
                              MessageBox(main_window_handle,
                              "5.5.5",
                              "bit mode detected...",
                              MB_OK | MB_ICONEXCLAMATION );
                              
                           }
                           break;
                        case 16:
                           {
                              // 5.6.5
                              g_rgb16bitmode = RGB16MODE_565;
                              makeColors565();
                              
                              MessageBox(main_window_handle,
                              "5.6.5",
                              "bit mode detected...",
                              MB_OK | MB_ICONEXCLAMATION );
                           }
                           break;
                        
                        case 24:
                           {
                              // 8.8.8
                           }
                           break;
                        
                        case 32:
                           {
                              // alpha(8) 8.8.8
                           }
                           break;
                           
                        default:
                           {
                           }
                        
                           break;
                     }
                  }
                  
                  retval = 1;            
               }
            }
         }
      }
   }

   // return success or failure or your own return code here
   return(retval);

} // end Game_Init