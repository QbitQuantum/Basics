void CCustomCmdTestDeviceSecurityCheck::SimulatePasswordEntry()
	{
    RWsSession wsSession;
    TInt err = wsSession.Connect();
    TEST(KErrNone == err);
    
    const TInt okButtonPos1 = 60; //the position of ok button
    const TInt okButtonPos2 = 600; //the position of ok button
    //Simulate the key press ,(comma) in to pin notifier dialogue
	TRawEvent eventDown;
	TRawEvent eventUp;

	eventDown.Set(TRawEvent::EKeyDown, EStdKeyComma);
	UserSvr::AddEvent(eventDown);
	eventUp.Set(TRawEvent::EKeyUp, EStdKeyComma);
	UserSvr::AddEvent(eventUp);
	User::After(100000);

	//Enter wrong pwd if iWrongPwd is ETrue
	if(iWrongPwd)
		{
		eventDown.Set(TRawEvent::EKeyDown, EStdKeyComma);
		UserSvr::AddEvent(eventDown);
		eventUp.Set(TRawEvent::EKeyUp, EStdKeyComma);
		UserSvr::AddEvent(eventUp);
		User::After(100000);
		
		//Reset it to false as wrong password should be entered only once
		iWrongPwd = EFalse;
		}

    eventDown.Set(TRawEvent::EButton1Down, okButtonPos1,okButtonPos2);
    UserSvr::AddEvent(eventDown);
    eventUp.Set(TRawEvent::EButton1Up, okButtonPos1,okButtonPos2);
    UserSvr::AddEvent(eventUp);
    User::After(100000);
    
    wsSession.Flush();
    wsSession.Close();
	}