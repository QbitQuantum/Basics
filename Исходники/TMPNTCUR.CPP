void CStatusWindow::Construct(CTestBase* aTest)
	{
	_LIT(Title,"StatusWindow");
	_LIT(String4,"Click here to finish");
	iTest=aTest;
	TWindowTitle title(Title);
	SetTitle(title);
	TInt yy=iTitleHeight+iFont->HeightInPixels()+7;
	iRect1.SetRect(3,iTitleHeight+5,iSize.iWidth-1,yy);
	TInt yy1=yy+iFont->HeightInPixels()+2;
	iRect2.SetRect(3,yy+3,iSize.iWidth-1,yy1);
	TInt yy2=yy1+iFont->HeightInPixels()+2;
	iRect3.SetRect(3,yy1+3,iSize.iWidth-1,yy2);
	iRect4.SetRect(3,yy2+3,iSize.iWidth-1,yy2+iFont->HeightInPixels()+2);
	TMachineInfoV1Buf machineInfo;
	UserHal::MachineInfo(machineInfo);
	iXyInputType=machineInfo().iXYInputType;
	iOriginalXyInputType=iXyInputType;
	iSimulatedPenDown=EFalse;
	//
	iString3.Copy(KNullDesC);
	if (iXyInputType==EXYInputDeltaMouse)
		{
		if (HAL::Get(HALData::EMouseState,iSimulatedPenDown)==KErrNone)
			UpdateString3();
		}
	UpdateString1();
	iMode=Client()->iWs.PointerCursorMode();
	iOriginalMode=iMode;
	UpdateString2();
	iUpdateNeeded=EFalse;
	iString4.Copy(String4);
	iExit=EFalse;
	}