void UMAInitToolbox( UInt16 inMoreMastersCalls, bool isEmbedded )
{
#if !TARGET_CARBON
    ::MaxApplZone();
    for (long i = 1; i <= inMoreMastersCalls; i++)
        ::MoreMasters();

    if (!isEmbedded)
    {
        ::InitGraf(&qd.thePort);
        ::InitFonts();
        ::InitMenus();
        ::TEInit();
        ::InitDialogs(0L);
        ::FlushEvents(everyEvent, 0);
    }

    long total,contig;
    PurgeSpace(&total, &contig);
#endif

    ::InitCursor();

    if ( Gestalt(gestaltSystemVersion, &sUMASystemVersion) != noErr)
        sUMASystemVersion = 0x0000 ;

    long theAppearance ;
    if ( Gestalt( gestaltAppearanceAttr, &theAppearance ) == noErr )
    {
        sUMAHasAppearance = true ;
        OSStatus status = RegisterAppearanceClient();
        // If status equals appearanceProcessRegisteredErr it means the
        // appearance client already was registered (For example if we run
        // embedded, the host might have registered it). In such a case
        // we don't unregister it later on.
        if (status != appearanceProcessRegisteredErr)
        {
            // Appearance client wasn't registered yet.
            sUMAHasInittedAppearance = true;
        }

        if ( Gestalt( gestaltAppearanceVersion, &theAppearance ) == noErr )
        {
            sUMAAppearanceVersion = theAppearance ;
        }
        else
        {
            sUMAAppearanceVersion = 0x0100 ;
        }
    }
    if ( Gestalt( gestaltWindowMgrAttr, &sUMAWindowManagerAttr ) == noErr )
    {
        sUMAHasWindowManager = sUMAWindowManagerAttr & gestaltWindowMgrPresent ;
    }

#if TARGET_CARBON
// Call currently implicitely done :        InitFloatingWindows() ;
#else
    if (!isEmbedded)
    {
        if ( sUMAHasWindowManager )
            InitFloatingWindows() ;
        else
            InitWindows();
    }
#endif

    if ( NavServicesAvailable() )
    {
        NavLoad() ;
    }

  long menuMgrAttr ;
  Gestalt( gestaltMenuMgrAttr , &menuMgrAttr ) ;
  if ( menuMgrAttr & gestaltMenuMgrAquaLayoutMask )
    sUMAHasAquaLayout = true ;

  if ( TXNInitTextension != (void*) kUnresolvedCFragSymbolAddress )
  {
    FontFamilyID fontId ;
    Str255 fontName ;
    SInt16 fontSize ;
    Style fontStyle ;
    GetThemeFont(kThemeSmallSystemFont , GetApplicationScript() , fontName , &fontSize , &fontStyle ) ;
    GetFNum( fontName, &fontId );

    TXNMacOSPreferredFontDescription fontDescriptions[] =
    {
        { fontId , (fontSize << 16) ,kTXNDefaultFontStyle, kTXNSystemDefaultEncoding }
    } ;
    int noOfFontDescriptions = sizeof( fontDescriptions ) / sizeof(TXNMacOSPreferredFontDescription) ;

      // kTXNAlwaysUseQuickDrawTextMask might be desirable because of speed increases but it crashes the app under OS X upon key stroke
#if 0
    // leads to unexpected content for clients, TODO configurable
    OptionBits options = kTXNWantMoviesMask | kTXNWantSoundMask | kTXNWantGraphicsMask ;
#else
    OptionBits options = 0 ;
#endif

#if TARGET_CARBON
    if ( !UMAHasAquaLayout() )
#endif
    {
        options |= kTXNAlwaysUseQuickDrawTextMask ;
    }
      TXNInitTextension(fontDescriptions,  noOfFontDescriptions, options );
  }


  UMASetSystemIsInitialized(true);

}