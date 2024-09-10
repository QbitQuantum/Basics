void init()
{
	RgnHandle			tempRgn;
	Rect				BaseRect;
	OSErr				err;
	long				QDfeature/*, OSfeature*/;
	GDHandle			SaveGD;
	CGrafPtr			SavePort;

	/*	Initialize Managaer.	*/
	//InitGraf(&qd.thePort);
	//InitWindows();
	//InitDialogs(nil);
	InitCursor();
	FlushEvents(everyEvent, 0);
	
	/*	Set up menus.	*/
	mymenu0 = GetMenu(appleID);
	//AppendResMenu(mymenu0, 'DRVR');
	InsertMenu(mymenu0,0);
	mymenu1 = GetMenu(fileID);
	InsertMenu(mymenu1,0);
	DrawMenuBar();
	DoneFlag = false;
	ThePict = GetPicture(PictID);
	if (ThePict == nil)
		DoneFlag = true;

	/*	Use Gestalt to find is QuickDraw is avaiable.	*/
	/*if ((GetOSTrapAddress(Gestalttest) != GetOSTrapAddress(NoTrap))) {
		err = Gestalt(gestaltQuickdrawVersion, &QDfeature);
		if (err)
			DoneFlag = true;
		err = Gestalt(gestaltSystemVersion, &OSfeature);
		if (err)
			DoneFlag = true;
		if (!DoneFlag && (QDfeature & 0x0f00) != 0x0200 && OSfeature < 0x0605)
			DoneFlag = true;
		}
	else
		DoneFlag = true;*/
	
	err = Gestalt(gestaltQuickdrawVersion, &QDfeature);
	if (err != noErr || QDfeature < gestalt32BitQD)
		DoneFlag = true;

	/*	Set Rects.	*/
	SetRect(&BaseRect, 40, 60, 472, 282);
	SetRect(&WinMinusScroll, BaseRect.left-40, BaseRect.top-60, BaseRect.right-60, 
				BaseRect.bottom - 80);
	SetRect(&InitWindowSize, WinMinusScroll.left, WinMinusScroll.top, 
							WinMinusScroll.right, WinMinusScroll.bottom);
	tempRgn = GetGrayRgn();
	HLock ((Handle) tempRgn);
	//TotalRect = (**tempRgn).rgnBBox;
	GetRegionBounds(tempRgn, &TotalRect);
	/*SetRect(&minRect, 80, 80, (**tempRgn).rgnBBox.right - 40, 
				(**tempRgn).rgnBBox.bottom - 40);*/
	SetRect(&minRect, 80, 80, TotalRect.right - 40, TotalRect.bottom - 40);
	HUnlock ((Handle) tempRgn);

	/*	Open window and set up picture.	*/
	GetGWorld (&SavePort, &SaveGD);
	mycolors = GetCTable (clutID);
	(*mycolors)->ctFlags |= 0x4000;

	myWindow = NewCWindow(nil, &BaseRect, (ConstStr255Param)"", true, zoomDocProc, 
							(WindowPtr) -1, true, 150);
	SetGWorld(GetWindowPort(myWindow), SaveGD);
	DrawGrowIcon (myWindow);

	srcPalette = NewPalette (((**mycolors).ctSize)+1, mycolors,
			pmTolerant + pmExplicit + pmAnimated, 0);
	SetPalette ((WindowPtr) myWindow, srcPalette, true);
	
	GetGWorld (&SavePort, &SaveGD);
	err = NewGWorld (&offscreenGWorld, 8, &InitWindowSize, mycolors, nil, 0);
	if (err)
		Debugger();
	SetGWorld (offscreenGWorld, nil);
	EraseRect (&InitWindowSize);
	DrawPicture (ThePict, &InitWindowSize);
	SetGWorld (SavePort, SaveGD);
}