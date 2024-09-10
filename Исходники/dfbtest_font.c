int
main( int argc, char *argv[] )
{
     int                    i;
     DFBResult              ret;
     DFBSurfaceDescription  desc;
     IDirectFB             *dfb;
     IDirectFBSurface      *dest            = NULL;
     const char            *url             = NULL;
     DFBFontAttributes      attributes      = DFFA_NONE;
     DFBSurfaceTextFlags    text_flags      = DSTF_TOPLEFT;
     int                    outline_width   = 0x10000;
     int                    outline_opacity = 255;
     const DFBColorID       color_ids[2]    = { DCID_PRIMARY, DCID_OUTLINE };
     const DFBColor         colors[2]       = { { 0xff, 0xff, 0xff, 0xff },
                                                { 0xff, 0x00, 0x80, 0xff } };

     /* Initialize DirectFB. */
     ret = DirectFBInit( &argc, &argv );
     if (ret) {
          D_DERROR( ret, "DFBTest/Font: DirectFBInit() failed!\n" );
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
          else if (strcmp (arg, "-o") == 0 || strcmp (arg, "--outline") == 0) {
               attributes |= DFFA_OUTLINED;
               text_flags |= DSTF_OUTLINE;
          }
          else if (strcmp (arg, "-ow") == 0 || strcmp (arg, "--outline-width") == 0) {
               if (++i == argc)
                    return print_usage( argv[0] );

               if (sscanf( argv[i], "%d", &outline_width ) != 1)
                    return print_usage( argv[0] );

               outline_width <<= 16;
          }
          else if (strcmp (arg, "-oo") == 0 || strcmp (arg, "--outline-opacity") == 0) {
               if (++i == argc)
                    return print_usage( argv[0] );

               if (sscanf( argv[i], "%d", &outline_opacity ) != 1)
                    return print_usage( argv[0] );
          }
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
          D_DERROR( ret, "DFBTest/Font: DirectFBCreate() failed!\n" );
          return ret;
     }

     /* Fill description for a primary surface. */
     desc.flags = DSDESC_CAPS;
     desc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;

     dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );

     /* Create a primary surface. */
     ret = dfb->CreateSurface( dfb, &desc, &dest );
     if (ret) {
          D_DERROR( ret, "DFBTest/Font: IDirectFB::CreateSurface() failed!\n" );
          goto out;
     }

     dest->GetSize( dest, &desc.width, &desc.height );
     dest->GetPixelFormat( dest, &desc.pixelformat );

     D_INFO( "DFBTest/Font: Destination is %dx%d using %s\n",
             desc.width, desc.height, dfb_pixelformat_name(desc.pixelformat) );

     for (i=10; i<50; i++) {
          IDirectFBFont *font;

          font = CreateFont( dfb, url, i, attributes, outline_width, outline_opacity );

          RenderChecker( dest, 64, 64 );

          dest->SetColors( dest, color_ids, colors, 2 );

          dest->SetFont( dest, font );
          dest->DrawString( dest, "Test String AVAWA", -1, 100, 100, text_flags );

          dest->Flip( dest, NULL, DSFLIP_NONE );

          font->Release( font );

          usleep( 500000 );
     }


out:
     if (dest)
          dest->Release( dest );

     /* Shutdown DirectFB. */
     dfb->Release( dfb );

     return ret;
}