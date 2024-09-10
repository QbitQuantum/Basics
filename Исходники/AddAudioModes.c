int
main( void )
{
  struct RDArgs *rdargs;
  int            rc = RETURN_OK;

  GfxBase       = (struct GfxBase *) OpenLibrary( GRAPHICSNAME, 37 );
  IntuitionBase = (struct IntuitionBase *) OpenLibrary( "intuition.library", 37 );
  
  if( GfxBase == NULL )
  {
    Printf( "Unable to open %s version %ld\n", (ULONG) GRAPHICSNAME, 37 );
    cleanup();
    return RETURN_FAIL;
  }

  if( IntuitionBase == NULL )
  {
    Printf( "Unable to open %s version %ld\n", (ULONG) "intuition.library", 37 );
    cleanup();
    return RETURN_FAIL;
  }

  rdargs = ReadArgs( TEMPLATE , (LONG *) &args, NULL );

  if( rdargs != NULL )
  {
    /* Refresh database */

    if( args.refresh && !args.remove )
    {
      ULONG id;

      OpenAHI();

      /* First, empty the database */
      
      for( id = AHI_NextAudioID( AHI_INVALID_ID );
           id != (ULONG) AHI_INVALID_ID;
           id = AHI_NextAudioID( AHI_INVALID_ID ) )
      {
        AHI_RemoveAudioMode( id );
      }

      /* Now add all modes */

      if( !AHI_LoadModeFile( "DEVS:AudioModes" ) )
      {
        if( IS_MORPHOS )
        {
          ULONG res;

          /* Be quiet here. - Piru */
          APTR *windowptr = &((struct Process *) FindTask(NULL))->pr_WindowPtr;
          APTR oldwindowptr = *windowptr;
          *windowptr = (APTR) -1;
          res = AHI_LoadModeFile( "MOSSYS:DEVS/AudioModes" );
          *windowptr = oldwindowptr;

          if( !res )
          {
            if( !args.quiet )
            {
              PrintFault( IoErr(), "AudioModes" );
            }

            rc = RETURN_ERROR;
          }
        }
        else
        {
          if ( !args.quiet )
          {
            PrintFault( IoErr(), "DEVS:AudioModes" );
          }

          rc = RETURN_ERROR;
        }
      }
    }

    /* Load mode files */

    if( args.files != NULL && !args.remove )
    {
      int i = 0;

      OpenAHI();

      while( args.files[i] )
      {
        if( !AHI_LoadModeFile( args.files[i] ) && !args.quiet )
        {
          PrintFault( IoErr(), args.files[i] );
          rc = RETURN_ERROR;
        }
        i++;
      }
    }

    /* Remove database */

    if( args.remove )
    {
      if( args.files || args.refresh )
      {
        PutStr( "The REMOVE switch cannot be used together with FILES or REFRESH.\n" );
        rc = RETURN_FAIL;
      }
      else
      {
        ULONG id;

        OpenAHI();

        for( id = AHI_NextAudioID( AHI_INVALID_ID );
             id != (ULONG) AHI_INVALID_ID;
             id = AHI_NextAudioID( AHI_INVALID_ID ) )
        {
          AHI_RemoveAudioMode( id );
        }
      }
    }

    /* Make display mode doublescan (allowing > 28 kHz sample rates) */

    if( args.dblscan )
    {
      ULONG          id;
      ULONG          bestid = INVALID_ID;
      int            minper = INT_MAX;
      struct Screen *screen = NULL;

      static const struct ColorSpec colorspecs[] =
      {
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        {-1, 0, 0, 0 }
      };
      
      union {
        struct MonitorInfo mon;
        struct DisplayInfo dis;
      } buffer;

      for( id = NextDisplayInfo( INVALID_ID );
           id != (ULONG) INVALID_ID;
           id = NextDisplayInfo( id ) )
      {
        int period;

        if( GetDisplayInfoData( NULL, 
                                (UBYTE*) &buffer.dis, sizeof(buffer.dis),
                                DTAG_DISP, id ) )
        {
          if( !(buffer.dis.PropertyFlags & (DIPF_IS_ECS | DIPF_IS_AA ) ) )
          {
            continue;
          }
        }

        if( GetDisplayInfoData( NULL,
                                (UBYTE*) &buffer.mon, sizeof(buffer.mon),
                                DTAG_MNTR, id ) )
        {
          period = buffer.mon.TotalColorClocks * buffer.mon.TotalRows
                   / ( 2 * ( buffer.mon.TotalRows - buffer.mon.MinRow + 1 ) );

          if( period < minper )
          {
            minper = period;
            bestid = id;
          }
        }

      }

      if( bestid != (ULONG) INVALID_ID && minper < 100 )
      {
        screen = OpenScreenTags( NULL,
                                 SA_DisplayID,  bestid,
                                 SA_Colors,    (ULONG) &colorspecs,
                                 TAG_DONE );
      }
      else if( ( GfxBase->ChipRevBits0 & (GFXF_HR_DENISE | GFXF_AA_LISA ) ) != 0 )
      {
        /* No suitable screen mode found, let's bang the hardware...
           Using code from Sebastiano Vigna <*****@*****.**>. */

        struct Custom *custom = (struct Custom *) 0xdff000;

        custom->bplcon0  = 0x8211;
        custom->ddfstrt  = 0x0018;
        custom->ddfstop  = 0x0058;
        custom->hbstrt   = 0x0009;
        custom->hsstop   = 0x0017;
        custom->hbstop   = 0x0021;
        custom->htotal   = 0x0071;
        custom->vbstrt   = 0x0000;
        custom->vsstrt   = 0x0003;
        custom->vsstop   = 0x0005;
        custom->vbstop   = 0x001D;
        custom->vtotal   = 0x020E;
        custom->beamcon0 = 0x0B88;
        custom->bplcon1  = 0x0000;
        custom->bplcon2  = 0x027F;
        custom->bplcon3  = 0x00A3;
        custom->bplcon4  = 0x0011;
      }

      if( screen != NULL )
      {
        CloseScreen( screen );
      }
    }

    FreeArgs( rdargs );
  }

  cleanup();
  return rc;
}