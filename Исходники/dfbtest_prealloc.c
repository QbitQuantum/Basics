int
main( int argc, char *argv[] )
{
     DFBResult               ret;
     int                     i;
     DFBSurfaceDescription   desc;
     IDirectFB              *dfb;
     IDirectFBSurface       *dest          = NULL;
     DFBSurfacePixelFormat   dest_format   = DSPF_UNKNOWN;
     char                    pixel_buffer[100*100*4];
     IDirectFBSurface       *source        = NULL;
     IDirectFBEventBuffer   *keybuffer;
     DFBInputEvent           evt;
     bool                    quit          = false;

     /* Initialize DirectFB. */
     ret = DirectFBInit( &argc, &argv );
     if (ret) {
          D_DERROR( ret, "DFBTest/PreAlloc: DirectFBInit() failed!\n" );
          return ret;
     }

     /* Parse arguments. */
     for (i=1; i<argc; i++) {
          const char *arg = argv[i];

          if (strcmp( arg, "-h" ) == 0 || strcmp (arg, "--help") == 0)
               return print_usage( argv[0] );
          else if (strcmp (arg, "-v") == 0 || strcmp (arg, "--version") == 0) {
               fprintf (stderr, "dfbtest_blit version %s\n", DIRECTFB_VERSION);
               return false;
          }
          else if (strcmp (arg, "-d") == 0 || strcmp (arg, "--dest") == 0) {
               if (++i == argc) {
                    print_usage (argv[0]);
                    return false;
               }

               if (!parse_format( argv[i], &dest_format ))
                    return false;
          }
          else if (strcmp (arg, "-s") == 0 || strcmp (arg, "--static") == 0) {
               static_caps = DSCAPS_STATIC_ALLOC;
          }
          else
               return print_usage( argv[0] );
     }

     /* Create super interface. */
     ret = DirectFBCreate( &dfb );
     if (ret) {
          D_DERROR( ret, "DFBTest/PreAlloc: DirectFBCreate() failed!\n" );
          return ret;
     }

     /* Fill description for a primary surface. */
     desc.flags = DSDESC_CAPS;
     desc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;

     if (dest_format != DSPF_UNKNOWN) {
          desc.flags       |= DSDESC_PIXELFORMAT;
          desc.pixelformat  = dest_format;
     }

     dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );

     /* Create an input buffer for key events */
     dfb->CreateInputEventBuffer( dfb, DICAPS_KEYS,
                                  DFB_TRUE, &keybuffer);

     /* Create a primary surface. */
     ret = dfb->CreateSurface( dfb, &desc, &dest );
     if (ret) {
          D_DERROR( ret, "DFBTest/PreAlloc: IDirectFB::CreateSurface() for the destination failed!\n" );
          goto out;
     }

     dest->GetSize( dest, &desc.width, &desc.height );
     dest->GetPixelFormat( dest, &desc.pixelformat );

     D_INFO( "DFBTest/PreAlloc: Destination is %dx%d using %s\n",
             desc.width, desc.height, dfb_pixelformat_name(desc.pixelformat) );

     /* Create a preallocated surface. */
     desc.flags                 = DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT | DSDESC_CAPS | DSDESC_PREALLOCATED;
     desc.width                 = 100;
     desc.height                = 100;
     desc.pixelformat           = DSPF_ARGB;
     desc.caps                  = static_caps;
     desc.preallocated[0].data  = pixel_buffer;
     desc.preallocated[0].pitch = 100 * 4;

     ret = dfb->CreateSurface( dfb, &desc, &source );
     if (ret) {
          D_DERROR( ret, "DFBTest/PreAlloc: IDirectFB::CreateSurface() for the preallocated source failed!\n" );
          goto out;
     }

     /* Before any other operation the pixel data can be written to without locking */
     gen_pixels( pixel_buffer, 100 * 4, 100 );

     while (!quit) {
          void *ptr;
          int   pitch;


          /* Lock source surface for writing before making updates to the pixel buffer */
          source->Lock( source, DSLF_WRITE, &ptr, &pitch );

          if (ptr == pixel_buffer)
               D_INFO( "DFBTest/PreAlloc: Locking preallocated source gave original preallocated pixel buffer :-)\n" );
          else {
               if (static_caps)
                    D_INFO( "DFBTest/PreAlloc: Locking preallocated source gave different pixel buffer, ERROR with static alloc!\n" );
               else
                    D_INFO( "DFBTest/PreAlloc: Locking preallocated source gave different pixel buffer, but OK (no static alloc)\n" );
          }

          update_pixels( ptr, pitch, 100 );

          /* Unlock source surface after writing, before making further Blits,
             to have the buffer be transfered to master again */
          source->Unlock( source );


          dest->Clear( dest, 0, 0, 0, 0xff );

          /* First Blit from preallocated source, data will be transfered to master */
          dest->Blit( dest, source, NULL, 50, 50 );

          /* Second Blit from preallocated source, data is already master */
          dest->Blit( dest, source, NULL, 150, 150 );

          dest->Flip( dest, NULL, DSFLIP_NONE );

          /* This will upload again the preallocated buffer to the master, where it is
             modified and outdates the preallocated buffer. Now it depends on the static
             alloc flag whether the next Lock will directly go into the shared memory
             allocation or the preallocated buffer again (with a transfer back from master
             to us). */
          source->FillRectangle( source, 0, 0, 10, 10 );

          /* Process keybuffer */
          while (keybuffer->GetEvent( keybuffer, DFB_EVENT(&evt)) == DFB_OK)
          {
              if (evt.type == DIET_KEYPRESS) {
                  switch (DFB_LOWER_CASE(evt.key_symbol)) {
                      case DIKS_ESCAPE:
                      case DIKS_SMALL_Q:
                      case DIKS_BACK:
                      case DIKS_STOP:
                      case DIKS_EXIT:
                          /* Quit main loop & test thread */
                          quit = true;
                          break;
                      default:
                          break;
                  }
              }
          }
          if (!quit)
          sleep( 5 );
     }

out:
     if (source)
          source->Release( source );

     if (dest)
          dest->Release( dest );

     keybuffer->Release( keybuffer );

     /* Shutdown DirectFB. */
     dfb->Release( dfb );

     return ret;
}