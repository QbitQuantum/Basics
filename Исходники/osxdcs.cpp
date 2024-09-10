Boolean MCScreenDC::open()
{
	owndnd = False;
	mouseMoveRgn = NewRgn();
	SetRectRgn(mouseMoveRgn, 0, 0, 1, 1);

	//create a invisible window, and set port to this window
	//so that later on at the very first time MC select and set font
	//will only affect in this invisible window, not other apps on the desk top,
	// when MC is first started.  The size of the window is random.
	//  Rect invisibleWinRect;
	Rect invisibleWinRect;
	SetRect(&invisibleWinRect, 0, 0, 20, 20);


	invisibleWin = NewCWindow(nil, &invisibleWinRect, "\p", False,
	                          kUtilityWindowClass, (WindowRef)(-1L), False, 0);



	long response;
	if (Gestalt(gestaltSystemVersion, &response) == noErr)
	{
		if (response >= 0x1030 && response < 0x1040)
			MCantialiasedtextworkaround = True;
		else
			MCantialiasedtextworkaround = False;
	}

	SetGWorld(GetWindowPort(invisibleWin), GetMainDevice());

	vis = new MCVisualInfo;
	
	devdepth = 32;

	black_pixel.red = black_pixel.green = black_pixel.blue = 0; //black pixel
	white_pixel.red = white_pixel.green = white_pixel.blue = 0xFFFF; //white pixel
		black_pixel.pixel = 0;
		white_pixel.pixel = 0xFFFFFF;

			redbits = greenbits = bluebits = 8;
			redshift = 16;
			greenshift = 8;
			blueshift = 0;
			vis->red_mask = 0x00FF0000;
			vis->green_mask = 0x0000FF00;
			vis->blue_mask = 0x000000FF;

	MCzerocolor = MCbrushcolor = white_pixel;
	alloccolor(MCbrushcolor);
	MCselectioncolor = MCpencolor = black_pixel;
	alloccolor(MCselectioncolor);
	alloccolor(MCpencolor);
	gray_pixel.red = gray_pixel.green = gray_pixel.blue = 0x8888;
	alloccolor(gray_pixel);
	background_pixel.red = background_pixel.green = background_pixel.blue = 0xffff;
	alloccolor(background_pixel);

	//query the system for the hilited text color, and set ours
	RGBColor hiliteRGB;
	LMGetHiliteRGB(&hiliteRGB);
	MChilitecolor.red = hiliteRGB.red;
	MChilitecolor.green = hiliteRGB.green;
	MChilitecolor.blue = hiliteRGB.blue;
	alloccolor(MChilitecolor);

	MCColor *syscolors = getaccentcolors();
	if (syscolors != NULL)
		MCaccentcolor = syscolors[4];
	else
	{
		MCaccentcolor.red = MCaccentcolor.green = 0x0000;
		MCaccentcolor.blue = 0x8080;
	}
	alloccolor(MCaccentcolor);

	grabbed = False;
	tripleclick = doubleclick = False;
	MCdoubletime = GetDblTime() * 1000 / 60;
	opened = True;
	mousewindow = new _Drawable;
	activewindow = new _Drawable;
	lastactivewindow = new _Drawable;
	mousewindow->type = activewindow->type = lastactivewindow->type = DC_WINDOW;
	mousewindow->handle.window = activewindow->handle.window
	                             = lastactivewindow->handle.window = 0;

	//get handle of application menu bar
	menuBar = GetMenuBar();
	SetMenuBar(menuBar);  //set menu bar as current menulist
	
	//create Apple menu
	appleMenu = NewMenu(mApple, "\p\024"); //menu title is an apple icon
	InsertMenuItem(appleMenu, "\pAbout...", 0);
	InsertMenu(appleMenu, 0);
	
	DrawMenuBar(); //draw the menu bar with the Apple menu
	usetemp = False;
	Handle tmem = Get1IndResource('TMEM', 1);
	if (tmem != NULL)
	{
		char *ptr = *tmem;
		if (*(ptr + 1))
			usetemp = True;
	}
	MCtemplatescrollbar->alloccolors();
	if (IsMacEmulatedLF()) // no AM
		MCtemplatebutton->allocicons();

	// preallocate these because GetItemMark can't distinguish them
	submenuIDs[0] = 1;
	submenuIDs[checkMark] = 1;
	submenuIDs[diamondMark] = 1;
	
	MCcursors[PI_NONE] = nil;
	MCblinkrate = GetCaretTime() * 1000 / 60;

	MCDisplay const *t_displays;
	getdisplays(t_displays, false);
	MCwbr = t_displays[0] . workarea;

	//TSM - INIT TSM APPLICATION AND INSTALL REQUIRED APPLEVENT HANDLERS
	TSMPositionToOffsetUPP = NewAEEventHandlerUPP(TSMPositionToOffset);
	TSMOffsetToPositionUPP = NewAEEventHandlerUPP(TSMOffsetToPosition);
	TSMUpdateHandlerUPP = NewAEEventHandlerUPP(TSMUpdateHandler);
	TSMUnicodeNotFromInputUPP
	= NewAEEventHandlerUPP(TSMUnicodeNotFromInputHandler);
	AEInstallEventHandler(kTextServiceClass, kPos2Offset,
	                      TSMPositionToOffsetUPP, 0L , False);
	AEInstallEventHandler(kTextServiceClass, kOffset2Pos,
	                      TSMOffsetToPositionUPP, 0L , False);
	AEInstallEventHandler(kTextServiceClass, kUpdateActiveInputArea,
	                      TSMUpdateHandlerUPP, 0L , False);
	AEInstallEventHandler(kTextServiceClass, kUnicodeNotFromInputMethod,
	                      TSMUnicodeNotFromInputUPP, 0L , False);
	openIME();

	dragdropUPP = NewDragReceiveHandlerUPP(DragReceiveHandler);
	InstallReceiveHandler(dragdropUPP, NULL, NULL);
	dragmoveUPP = NewDragTrackingHandlerUPP(DragTrackingHandler);
	InstallTrackingHandler(dragmoveUPP, NULL, NULL);
	
	s_animation_current_time = s_animation_start_time = CFAbsoluteTimeGetCurrent();
	
	//// Dock Menu Initialization
	
	EventTypeSpec t_menu_event_specs[1];
	t_menu_event_specs[0] . eventClass = kEventClassMenu;
	t_menu_event_specs[0] . eventKind = kEventMenuPopulate;
	
	CreateNewMenu(0, 0, &f_icon_menu);
	s_icon_menu_event_handler_upp = NewEventHandlerUPP((EventHandlerProcPtr)handleiconmenuevent);
	InstallEventHandler(GetMenuEventTarget(f_icon_menu), s_icon_menu_event_handler_upp, 1, t_menu_event_specs, NULL, NULL);
	
	t_menu_event_specs[0] . eventClass = kEventClassCommand;
	t_menu_event_specs[0] . eventKind = kEventCommandProcess;
	InstallEventHandler(GetApplicationEventTarget(), s_icon_menu_event_handler_upp, 1, t_menu_event_specs, NULL, NULL);
	
	SetApplicationDockTileMenu(f_icon_menu);
	
	//// Color Profile Initialization
	
	CMGetDefaultProfileBySpace(cmRGBData, &m_dst_profile);

	CMProfileLocation t_location;
	t_location . locType = cmPathBasedProfile;
	strcpy(t_location . u . pathLoc . path, "/System/Library/ColorSync/Profiles/sRGB Profile.icc");
	CMOpenProfile(&m_srgb_profile, &t_location);
	
	////
	
	return True;
}