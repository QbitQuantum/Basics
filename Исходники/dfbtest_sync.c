int
main( int argc, char *argv[] )
{
     int                     i;
     DFBResult               ret;
     DFBSurfaceDescription   desc;
     IDirectFB              *dfb;
     IDirectFBImageProvider *provider      = NULL;
     IDirectFBSurface       *source        = NULL;
     IDirectFBSurface       *dest          = NULL;
     const char             *url           = NULL;
     DFBSurfacePixelFormat   source_format = DSPF_UNKNOWN;
     DFBSurfacePixelFormat   dest_format   = DSPF_UNKNOWN;
     bool                    dest_resize   = false;

     /* Initialize DirectFB. */
     ret = DirectFBInit( &argc, &argv );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: DirectFBInit() failed!\n" );
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
          else if (strcmp (arg, "-s") == 0 || strcmp (arg, "--source") == 0) {
               if (++i == argc) {
                    print_usage (argv[0]);
                    return false;
               }

               if (!parse_format( argv[i], &source_format ))
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
          else if (strcmp (arg, "-r") == 0 || strcmp (arg, "--resize") == 0)
               dest_resize = true;
          else if (!url)
               url = arg;
          else
               return print_usage( argv[0] );
     }

     /* Check if we got an URL. */
     if (!url)
          return print_usage( argv[0] );
          
     /* Create super interface. */
     ret = DirectFBCreate( &dfb );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: DirectFBCreate() failed!\n" );
          return ret;
     }

     /* Create an image provider for the image to be loaded. */
     ret = dfb->CreateImageProvider( dfb, url, &provider );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: IDirectFB::CreateImageProvider( '%s' ) failed!\n", url );
          goto out;
     }

     /* Get the surface description. */
     ret = provider->GetSurfaceDescription( provider, &desc );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: IDirectFBImageProvider::GetSurfaceDescription() failed!\n" );
          goto out;
     }

     if (source_format != DSPF_UNKNOWN)
          desc.pixelformat = source_format;
     
     D_INFO( "DFBTest/Blit: Source is %dx%d using %s\n",
             desc.width, desc.height, dfb_pixelformat_name(desc.pixelformat) );

     /* Create a surface for the image. */
     ret = dfb->CreateSurface( dfb, &desc, &source );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: IDirectFB::CreateSurface() failed!\n" );
          goto out;
     }
     
     ret = provider->RenderTo( provider, source, NULL );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: IDirectFBImageProvider::RenderTo() failed!\n" );
          goto out;
     }

     /* Fill description for a primary surface. */
     desc.flags = DSDESC_CAPS;
     desc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;

     if (dest_format != DSPF_UNKNOWN) {
          desc.flags       |= DSDESC_PIXELFORMAT;
          desc.pixelformat  = dest_format;
     }

     if (dest_resize)
          desc.flags |= DSDESC_WIDTH | DSDESC_HEIGHT;

     dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );

     /* Create a primary surface. */
     ret = dfb->CreateSurface( dfb, &desc, &dest );
     if (ret) {
          D_DERROR( ret, "DFBTest/Blit: IDirectFB::CreateSurface() failed!\n" );
          goto out;
     }

     dest->GetSize( dest, &desc.width, &desc.height );
     dest->GetPixelFormat( dest, &desc.pixelformat );

     D_INFO( "DFBTest/Blit: Destination is %dx%d using %s\n",
             desc.width, desc.height, dfb_pixelformat_name(desc.pixelformat) );

     for (i=0; i<100000; i++) {
          int j,n = rand()%100;

          for (j=0; j<n; j++) {
               switch (rand()%3) {
                    case 0:
                         dest->SetDrawingFlags( dest, rand() & (DSDRAW_BLEND) );
                         dest->FillRectangle( dest, rand()%100, rand()%100, rand()%100, rand()%100 );
                         break;

                    case 1:
                         dest->SetBlittingFlags( dest, rand() & (DSBLIT_BLEND_ALPHACHANNEL |
                                                                 DSBLIT_BLEND_COLORALPHA   |
                                                                 DSBLIT_COLORIZE           |
                                                                 DSBLIT_ROTATE90) );
                         dest->Blit( dest, source, NULL, rand()%100, rand()%100 );
                         break;

                    case 2:
                         dest->SetBlittingFlags( dest, rand() & (DSBLIT_BLEND_ALPHACHANNEL |
                                                                 DSBLIT_BLEND_COLORALPHA   |
                                                                 DSBLIT_COLORIZE           |
                                                                 DSBLIT_ROTATE90) );
                         dest->StretchBlit( dest, source, NULL, NULL );
                         break;
               }
          }

          dfb->WaitIdle( dfb );

          dest->Flip( dest, NULL, DSFLIP_NONE );
     }

out:
     if (dest)
          dest->Release( dest );

     if (source)
          source->Release( source );

     if (provider)
          provider->Release( provider );

     /* Shutdown DirectFB. */
     dfb->Release( dfb );

     return ret;
}