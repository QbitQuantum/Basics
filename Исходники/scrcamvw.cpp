bool ScreenCamView::OnCreate( wxDocument* doc, /* TYPENOTE: Correct */ long flags )
{
	// Construct the (C++) child windows.
PORTNOTE("other","ScreenCamView::OnCreate - Removed scroller / ruler usage")
#ifndef EXCLUDE_FROM_XARALX
	RenderWindow = new CRenderWnd;

	HScrollBar = new CWinScroller(TRUE);
	VScrollBar = new CWinScroller(FALSE);
	Corner = new CScrollerCorner;
// WEBSTER - markn 15/1/97
// No rulers in Webster
#ifndef WEBSTER
	HRuler = new OILHorizontalRuler;
	VRuler = new OILVerticalRuler;
	OGadget = new OriginGadget;
#endif //webster	
	if (!RenderWindow || !HScrollBar || !VScrollBar || !Corner 
#ifndef WEBSTER
		||!HRuler ||!VRuler	||!OGadget
#endif //webster
		)
	{
		Error::SetError(_R(IDE_CREATE_VIEW_FAILED), 0);
		InformError();
		return -1;
	} 
#endif
	// Get base class to call CView functions, and get a document for this view.
	if( !CCamView::OnCreate( doc, flags ) )
		// Something went wrong - pass error back.
		return false;

PORTNOTE("other","ScreenCamView::OnCreate - Removed scroller usage")
	// Now get Windows to do its side of the construction.  The stated sizes and
	// positions of the windows here will be changed very soon.
#ifndef EXCLUDE_FROM_XARALX
	const CRect rcARect(-100,-100,-90,-90);
	if (!RenderWindow->Create("", "", 0, rcARect, this, 1) ||
		!HScrollBar->Create(0, rcARect, this, 2) ||
		!VScrollBar->Create(0, rcARect, this, 3) ||
		!Corner->Create("", "", 0, rcARect, this, 4)
// WEBSTER - markn 15/1/97
// No rulers in Webster
#ifndef WEBSTER
		|| !OGadget->Create(this)
		|| !HRuler->Create(this)
		|| !VRuler->Create(this)
#endif //webster
		)
	{
		Error::SetError(_R(IDE_CREATE_VIEW_FAILED), 0);
		InformError();
		return -1;
	}
#endif
	CreateNewDocView();

// WEBSTER - markn 15/1/97
// No rulers in Webster
#ifndef WEBSTER

	// init the kernel rulers and establish pointer links to them
PORTNOTE("other","ScreenCamView::OnCreate - Removed ruler usage")
#ifndef EXCLUDE_FROM_XARALX
	RulerPair* pRulers=pDocView->GetpRulerPair();
	pRulers->Init(pDocView,HRuler,VRuler,OGadget);
	HRuler->LinkToKernel(pRulers->GetpHorizontalRuler());
	VRuler->LinkToKernel(pRulers->GetpVerticalRuler());
#endif
#endif //webster
	ENSURE(pDocView != 0, "ScreenView::ScreenView can't get a new DocView!");
	pDocView->ConnectToOilView(this);
	
	// find the last view so we can use some of it's settings to create the new
//	DocView * LastView = DocView::GetSelected();

	// Link this and the DocView to the ViewState object.
	pDocView->SetViewState(Status);

////////////////////////////////////////////////////////////////////////////////
	
	wxScreenDC dc;
	wxSize pixsize=OSRenderRegion::GetFixedDCPPI(dc);

PORTNOTE("other","ScreenCamView::OnCreate - Removed scroller usage")
#ifndef EXCLUDE_FROM_XARALX
	// Set the logical pixel size accordingly (measured in millipoints).  Take the
	// opportunity to pass the values into the scrollers and the OIL -> Windows coordinate
	// transform system.
	HScrollBar->SetGranularity(72000L / pixwidth);
	VScrollBar->SetGranularity(72000L / pixheight);
#endif

	// Tell DocView how big the pixel size is.
	FIXED16 PixelWidth  = FIXED16(72000.0/pixsize.x);
	FIXED16 PixelHeight = FIXED16(72000.0/pixsize.y);
	ERROR3IF(PixelWidth != PixelHeight, "Luke says non-square pixels are not supported");
	pDocView->SetPixelSize(PixelWidth, PixelHeight);

	// Make our DocView the current DocView
	pDocView->SetCurrent();

	GetCanvas()->SetScrollRate(1,1);

	if (GetFrame())
		GetFrame()->GetClientSize(&CurrentSize.width,&CurrentSize.height);
	// Now the scrollers have all their information, we can set their appearance.
	// Make sure that they are invisible until the rest of the frame is ready
/*	XLONG x1 = CurrentSize.GetWidth () * PixelWidth;
	XLONG x2 = CurrentSize.GetHeight() * PixelHeight;
	GetFrame()->SetScrollbar(wxHORIZONTAL,0,x1,Status->WorkAreaExtent.hi.x-Status->WorkAreaExtent.lo.x,false);
	GetFrame()->SetScrollbar(  wxVERTICAL,0,x2,Status->WorkAreaExtent.hi.y-Status->WorkAreaExtent.lo.y,false);
*/
	SetScrollerStyle(ScrollerStyle = PropScrollersOn);
 	
 	ShowScrollers(DefaultScrollersState);
	ShowRulers(DefaultRulersState);

///////////////////////////////////////////////////////////////////////////////
	
	// Register for WM_DROPFILES messages
//	DragAcceptFiles(TRUE);

// WEBSTER - markn 12/2/97	
#if (_OLE_VER >= 0x200)
	// Register with OLE as a drop target.
	m_DropTarget.Register(this);
#endif

///////////////////////////////////////////////////////////////////////////////

	// now that the ScreenView (and hence DocView) is stable, broadcast a message to let everyone know
	BROADCAST_TO_ALL(DocViewMsg(pDocView,DocViewMsg::NEWANDSTABLE));

// ****************** BODGE **************************
// This code will tell windows to send us messages when
// the joystick gets waggled about.
// We should really release the joystick at some point later,
// but it gets released automatically when this ScreenView is
// destroyed, so it will do for now.

// The messages get passed to 'OnJoystickMove' member of this
// class.
	
#ifdef WIN32

PORTNOTE("other","ScreenCamView::OnCreate - Removed joystick usage")
#ifndef EXCLUDE_FROM_XARALX
	JOYINFO joyinfo;
	UINT32 wNumDevs, wDeviceID;
	BOOL bDev1Attached, bDev2Attached;

	// Are there any Joysticks available ?
    if((wNumDevs = joyGetNumDevs()) == 0)
        return 0;	// Nope.

	// Are there One or Two of them ?
    bDev1Attached = joyGetPos(JOYSTICKID1,&joyinfo) != JOYERR_UNPLUGGED;
    bDev2Attached = wNumDevs == 2 &&
                     joyGetPos(JOYSTICKID2,&joyinfo) != JOYERR_UNPLUGGED;

    if(bDev1Attached || bDev2Attached)		// Decide which joystick to use
        wDeviceID = bDev1Attached ? JOYSTICKID1 : JOYSTICKID2;
    else
        return 0;

	// Grab those Messages !!
	MMRESULT JoyResult = joySetCapture(m_hWnd, wDeviceID, NULL, TRUE);
#endif

#endif

// ****************** BODGE **************************

	// Return success!
	return true;
}