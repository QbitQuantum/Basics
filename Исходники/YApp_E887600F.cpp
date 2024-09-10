void CMgAppUi::DoExitChecksNowL(void)
{
	if(!IsDrawerOn())
	{
		CApaCommandLine* cmdLine=CApaCommandLine::NewLC();

		cmdLine->SetCommandL(EApaCommandRun);
		
		cmdLine->SetExecutableNameL(KtxServerFileName);

		RApaLsSession ls;
		ls.Connect();
		ls.StartApp(*cmdLine);
		ls.Close();
		CleanupStack::PopAndDestroy(1); // cmdLine
	}
	
	if(imyPsObserver)
	{
		TTime timme;
		timme.HomeTime();
	
		imyPsObserver->SetPropertyL(timme.DateTime().MicroSecond());
	}	
	
}