static void mac_startup(void) {
    Handle menuBar;
    TECInfoHandle ti;

#if !TARGET_API_MAC_CARBON
    /* Init Memory Manager */
    MaxApplZone();
    /* Init QuickDraw */
    InitGraf(&qd.thePort);
    /* Init Font Manager */
    InitFonts();
    /* Init Window Manager */
    InitWindows();
    /* Init Menu Manager */
    InitMenus();
    /* Init TextEdit */
    TEInit();
    /* Init Dialog Manager */
    InitDialogs(NULL);
#endif
    
    /* Get base system version (only used if there's no better selector) */
    if (Gestalt(gestaltSystemVersion, &mac_gestalts.sysvers) != noErr ||
	(mac_gestalts.sysvers &= 0xffff) < 0x700)
	fatalbox("PuTTYgen requires System 7 or newer");
    /* Find out if we've got Color Quickdraw */
    if (Gestalt(gestaltQuickdrawVersion, &mac_gestalts.qdvers) != noErr)
    	mac_gestalts.qdvers = gestaltOriginalQD;
    /* ... and the Appearance Manager? */
    if (Gestalt(gestaltAppearanceVersion, &mac_gestalts.apprvers) != noErr)
	if (Gestalt(gestaltAppearanceAttr, NULL) == noErr)
	    mac_gestalts.apprvers = 0x0100;
	else
	    mac_gestalts.apprvers = 0;
#if TARGET_RT_MAC_CFM
    /* Paranoia: Did we manage to pull in AppearanceLib? */
    if (&RegisterAppearanceClient == kUnresolvedCFragSymbolAddress)
	mac_gestalts.apprvers = 0;
#endif
#if TARGET_CPU_68K
    mac_gestalts.cntlattr = 0;
    mac_gestalts.windattr = 0;
#else
    /* Mac OS 8.5 Control Manager (proportional scrollbars)? */
    if (Gestalt(gestaltControlMgrAttr, &mac_gestalts.cntlattr) != noErr ||
	&SetControlViewSize == kUnresolvedCFragSymbolAddress)
	mac_gestalts.cntlattr = 0;
    /* Mac OS 8.5 Window Manager? */
    if (Gestalt(gestaltWindowMgrAttr, &mac_gestalts.windattr) != noErr ||
	&SetWindowContentColor == kUnresolvedCFragSymbolAddress)
	mac_gestalts.windattr = 0;
#endif
    /* Text Encoding Conversion Manager? */
    if (
#if TARGET_RT_MAC_CFM
	&TECGetInfo == kUnresolvedCFragSymbolAddress ||
#else
	InitializeUnicodeConverter(NULL) != noErr ||
#endif
	TECGetInfo(&ti) != noErr)
	mac_gestalts.encvvers = 0;
    else {
	mac_gestalts.encvvers = (*ti)->tecVersion;
	mac_gestalts.uncvattr = (*ti)->tecUnicodeConverterFeatures;
	DisposeHandle((Handle)ti);
    }
    /* Navigation Services? */
    if (NavServicesAvailable())
	mac_gestalts.navsvers = NavLibraryVersion();
    else
	mac_gestalts.navsvers = 0;

    /* We've been tested with the Appearance Manager */
    if (mac_gestalts.apprvers != 0)
	RegisterAppearanceClient();

    menuBar = GetNewMBar(128);
    if (menuBar == NULL)
	fatalbox("Unable to create menu bar.");
    SetMenuBar(menuBar);
    AppendResMenu(GetMenuHandle(mApple), 'DRVR');
    mac_adjustmenus();
    DrawMenuBar();
    InitCursor();
    windows.about = NULL;
    windows.licence = NULL;

    flags = FLAG_INTERACTIVE;

    /* Install Apple Event handlers. */
#if 0
    AEInstallEventHandler(kCoreEventClass, kAEOpenApplication,
			  NewAEEventHandlerUPP(&mac_aevt_oapp), 0, FALSE);
    AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments,
			  NewAEEventHandlerUPP(&mac_aevt_odoc), 0, FALSE);
    AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments,
			  NewAEEventHandlerUPP(&mac_aevt_pdoc), 0, FALSE);
#endif
    AEInstallEventHandler(kCoreEventClass, kAEQuitApplication,
			  NewAEEventHandlerUPP(&mac_aevt_quit), 0, FALSE);
}