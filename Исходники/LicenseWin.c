void
InLicenseContent(EventRecord* evt, WindowPtr wCurrPtr)
{
	Point 			localPt;
	Rect			r;
	ControlPartCode	part;
	short 			code, value;
	ControlHandle	scrollBar;
	ControlActionUPP	scrollActionFunctionUPP;
	GrafPtr			oldPort;
	
	GetPort(&oldPort);
	SetPort(gWPtr);
	localPt = evt->where;
	GlobalToLocal( &localPt);
	
	code = FindControl(localPt, wCurrPtr, &scrollBar);
	switch (code)
	{
		case kControlUpButtonPart:
		case kControlDownButtonPart:
		case kControlPageUpPart:
		case kControlPageDownPart:
			scrollActionFunctionUPP = NewControlActionUPP(DoScrollProc);
			value = TrackControl(scrollBar, localPt, scrollActionFunctionUPP);
 			return;
			
		case kControlIndicatorPart:
			value = GetControlValue(scrollBar);
			code = TrackControl(scrollBar, localPt, nil);
			if (code) 
			{
				value -= GetControlValue(scrollBar);
				if (value) 
				{
					TEScroll(0, value * kScrollAmount, gControls->lw->licTxt);
                    ShowTxt();
				}
			}
			return;
	}
	
	HLock((Handle)gControls->backB);
	r = (**(gControls->backB)).contrlRect;
	HUnlock((Handle)gControls->backB);
	if (PtInRect( localPt, &r))
	{
		part = TrackControl(gControls->backB, evt->where, NULL);
		if (part)
			gDone = true;  /* Decline pressed */
	}
	
	HLock((Handle)gControls->nextB);			
	r = (**(gControls->nextB)).contrlRect;
	HUnlock((Handle)gControls->nextB);
	if (PtInRect( localPt, &r))
	{
		part = TrackControl(gControls->nextB, evt->where, NULL);
		if (part)
		{
			KillControls(gWPtr);
			ShowSetupTypeWin();
			return;
		}
	}
	
	ShowTxt();
	// TO DO
	SetPort(oldPort);
}