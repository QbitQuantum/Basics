static void ROM_ShowMenuBar(_THIS)
{
#if !TARGET_API_MAC_CARBON /* This seems not to be available? -sts Aug 2000 */
	RgnHandle		drawRgn = nil;
	RgnHandle		menuRgn = nil;
	RgnHandle		tempRgn = nil;
	RgnHandle		grayRgn = nil;
	WindowPtr		window = nil;
	GrafPtr			wMgrPort;
	GrafPtr			savePort;
	Rect			menuRect;
	long			response;
	short			height;
	EventRecord		theEvent;
	RGBColor		saveRGB;
	RGBColor		blackRGB = { 0, 0, 0 };

	height = GetMBarHeight();
	
	if ((height <= 0) && (gSaveMenuBar > 0)) {
		drawRgn = NewRgn();
		menuRgn = NewRgn();
		tempRgn = NewRgn();
		if ( ! tempRgn || ! drawRgn || ! gSaveGrayRgn ) {
			goto CLEANUP;
		}
		grayRgn = GetGrayRgn(); /* No need to check for this */
	
		GetPort(&savePort);
		GetWMgrPort(&wMgrPort);

		/* Set the height properly */
		LMSetMBarHeight(gSaveMenuBar);

		/* Restore the old GrayRgn: rounded corners, etc, but not
		   the menubar -- subtract that out first! */
		if (gSaveGrayRgn)
			{
			menuRect = (*GetMainDevice())->gdRect;
			menuRect.bottom = menuRect.top + gSaveMenuBar;
			RectRgn(menuRgn, &menuRect);

			DiffRgn(grayRgn, gSaveGrayRgn, drawRgn); 	/* What do we inval? */
			DiffRgn(drawRgn, menuRgn, drawRgn);			/* Clip out the menu */
			
			/* Now redraw the corners and other bits black */
			SetPort(wMgrPort);
			GetClip(tempRgn);
			SetClip(drawRgn);
			GetForeColor(&saveRGB);
			RGBForeColor(&blackRGB);
			PaintRgn(drawRgn);
			RGBForeColor(&saveRGB);
			SetClip(tempRgn);
			SetPort(savePort);
			
			UnionRgn(drawRgn, menuRgn, drawRgn);		/* Put back the menu */

			/* Now actually restore the GrayRgn */
			CopyRgn(gSaveGrayRgn, grayRgn);
			DisposeRgn(gSaveGrayRgn);
			gSaveGrayRgn = nil;
			}

		/* Modify the vis regions of exposed windows and draw menubar */
		window = (FrontWindow()) ? FrontWindow() : (WindowPtr) -1L;
		PaintBehind(window, drawRgn);
		CalcVisBehind(window, drawRgn);
		DrawMenuBar();

		SetPort(savePort);
		gSaveMenuBar = 0;

		/* Now show the control strip if it's present */
		if (!Gestalt(gestaltControlStripAttr, &response) && 
				(response & (1L << gestaltControlStripExists)))
			{
			if (gSaveCSVis && !SBIsControlStripVisible())
				SBShowHideControlStrip(true);
			gSaveCSVis = true;
			}

		/* Yield time so that floaters can catch up */
		EventAvail(0, &theEvent);
		EventAvail(0, &theEvent);
		EventAvail(0, &theEvent);
		EventAvail(0, &theEvent);
		}

CLEANUP:

	if (drawRgn) DisposeRgn(drawRgn);
	if (menuRgn) DisposeRgn(menuRgn);
	if (tempRgn) DisposeRgn(tempRgn);
#endif /* !TARGET_API_MAC_CARBON */
}