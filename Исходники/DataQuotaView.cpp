void CDataQuotaView::OpenWebBrowserL(const TDesC& aUrl,
									 const TBool aForceNative)
	{
	// To suppress compiler warnings
	(void)aUrl;
	(void)aForceNative;

#ifdef __OVI_SIGNED__
	RApaLsSession lsSession;
	User::LeaveIfError(lsSession.Connect());
	CleanupClosePushL(lsSession); 

	const TUid KBrowserUid = {0x10008D39};
	TUid handlerUid = KBrowserUid;

	if (!aForceNative)
		{
		// Find the default browser, on S^1/S^3 it may be a 3rd party browser
		_LIT8(KMimeDataType, "application/x-web-browse");
		TDataType mimeDataType(KMimeDataType);
		// Get the default application UID for "application/x-web-browse"
		lsSession.AppForDataType(mimeDataType, handlerUid);
	
		if (handlerUid.iUid == 0)
			{
			// For S60 3.x
			handlerUid = KBrowserUid;
			}
		}
	
	TApaTaskList taskList(CEikonEnv::Static()->WsSession());
	TApaTask task(taskList.FindApp(handlerUid));
	if(task.Exists())
		{
		task.BringToForeground();
		HBufC8* param8(HBufC8::NewLC(aUrl.Length()));
		param8->Des().Append(aUrl);
		task.SendMessage(TUid::Uid(0), *param8); // UID not used
		CleanupStack::PopAndDestroy(param8);
		}
	else
		{
		TThreadId thread;
		User::LeaveIfError(lsSession.StartDocument(aUrl, handlerUid, thread));
		}
	CleanupStack::PopAndDestroy(&lsSession);

#else // !__OVI_SIGNED__

	if (!iBrowserLauncher)
		{
		iBrowserLauncher = CBrowserLauncher::NewL();
		}
	iBrowserLauncher->LaunchBrowserEmbeddedL(aUrl);
#endif // __OVI_SIGNED__
	}