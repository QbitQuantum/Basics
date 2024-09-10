TVerdict CShutdownApp::doTestStepL()
	{
	TInt uidValue;
	_LIT(KUidKey, "uid");
	if (!GetHexFromConfig(ConfigSection(), KUidKey, uidValue))
		{
		ERR_PRINTF1(_L("Missing uid"));
		SetTestStepResult(EFail);
		return EFail;
		}
	TInt connectErr = KErrNotFound;
#ifndef SWI_TEXTSHELL_ROM
	TUid appUid;
	appUid.iUid = uidValue;

	TInt wgId=0;
	RWsSession wsSession;
	connectErr = wsSession.Connect();
	if (connectErr != KErrNotFound)
		{
		User::LeaveIfError(connectErr);
		CleanupClosePushL(wsSession);
		
		CApaWindowGroupName* wgName = CApaWindowGroupName::NewL(wsSession);
		CleanupStack::PushL(wgName);
		CApaWindowGroupName::FindByAppUid(appUid, wsSession, wgId);
		
		if (wgId == KErrNotFound)
			{
			ERR_PRINTF2(_L("Running app with UID 0x%x not found."), appUid.iUid);		
			User::Leave(KErrNotFound);
			}
		
		wgName->ConstructFromWgIdL(wgId);
		
		if(wgName->RespondsToShutdownEvent())
			{
			TApaTask task(wsSession);
			task.SetWgId(wgId);
			RThread thread;
			TInt err=thread.Open(task.ThreadId());
			CleanupClosePushL(thread);
			if (!err)
				{
				RProcess process;
				thread.Process(process);
				CleanupClosePushL(process);
				
				TRequestStatus processStatus;
				process.Rendezvous(processStatus);
					
				task.SendSystemEvent(EApaSystemEventShutdown);

				RTimer timer;
				CleanupClosePushL(timer);
				TRequestStatus timerStatus;
				
				User::LeaveIfError(timer.CreateLocal());
				timer.After(timerStatus, KAppShutdownTimeout);

				User::WaitForRequest(processStatus,timerStatus);

				if (processStatus==KRequestPending)
					{
					// timer completed so give up
					process.RendezvousCancel(processStatus);
					User::WaitForRequest(processStatus);
					ERR_PRINTF2(_L("App with UID 0x%x timed out on shutdown."), appUid.iUid);		
					User::Leave(KErrTimedOut);
					}
				else if (timerStatus==KRequestPending)
					{
					// Rendezvous completed so cancel timer
					timer.Cancel();
					User::WaitForRequest(timerStatus);
					}
				else
					{
					 // Both have completed, so prevent stray request
					User::WaitForRequest(processStatus,timerStatus);
					}
					
				CleanupStack::PopAndDestroy(2, &process);
				INFO_PRINTF2(_L("App with UID 0x%x shut down."), appUid.iUid);
				SetTestStepResult(EPass);

				}
			CleanupStack::PopAndDestroy(&thread);
			}
		else 
			{
			ERR_PRINTF2(_L("App with UID %x does not handle shutdown events."), appUid.iUid);
			SetTestStepResult(EFail);
			}
		CleanupStack::PopAndDestroy(2, &wsSession);
	}
#endif
	if (connectErr == KErrNotFound)
		{
		// emulator tests running in textshell or in textshell ROM (#def SWI_TEXTSHELL_ROM)
		ERR_PRINTF1(_L("Ignoring shutdown checks in Textshell Rom"));
		}
	return TestStepResult();
	}