/**	Test using an indipendent method that GCE version of WServ is running
 *  This method can be called at any time, even by external code, but creates temporary window session objects
 * 
 * 	@return	true if WServ version is GCE technology, false if legacy technology
 **/
TBool CWsGceCscBase::GCEIsSupportedStatic()
	{
	CFbsDrawDevice* screenDevice=NULL;
	RWsSession session;
	if (session.Connect()!=KErrNone)
		{
		return EFalse;
		}
	CWsScreenDevice screen(session);
	if (screen.Construct(TGlobalSettings::Instance().iScreen)!=KErrNone)
		{
		return EFalse;
		}
	
	TDisplayMode displayMode=screen.DisplayMode();
	TRAPD(err, screenDevice = CFbsDrawDevice::NewScreenDeviceL(TGlobalSettings::Instance().iScreen, displayMode));
	TBool rv=EFalse;
	if(err == KErrNone)
		{
		TAny* p=NULL;
		rv=(screenDevice->GetInterface(KSurfaceInterfaceID, p)==KErrNone);
		delete screenDevice;
		}
	return rv;
	}