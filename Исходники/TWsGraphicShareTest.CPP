void CWsGraphicShareBase::ConstructL()
	{
	User::LeaveIfError(iWs.Connect());
	iScreen=new(ELeave) CWsScreenDevice(iWs);
	User::LeaveIfError(iScreen->Construct(iScreenNumber));
	iGc=new(ELeave) CWindowGc(iScreen);
	User::LeaveIfError(iGc->Construct());
	iGroupWin=new(ELeave) RWindowGroup(iWs);
	iGroupWin->Construct(1);
		
	iWin=new(ELeave) RWindow(iWs);
	iWin->Construct(*iGroupWin,ENullWsHandle);
	iWin->SetRequiredDisplayMode(EColor256);
	iWin->SetExtent(TPoint(0,0),iScreen->SizeInPixels());
	iWin->Activate();
	iWin->BeginRedraw();
	iWin->EndRedraw();
	iWs.Flush();
	}	