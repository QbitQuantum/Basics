void CStepProcRestart::Cleanup()
	{
	RTestProcGoodSession server;	
	const TInt err = server.Connect();
	TESTE(KErrNone == err, err);
	if(KErrNone == err)
		{
		INFO_PRINTF1(_L("Going to cancel monitor and shutdown server."));		
		}
	server.CancelMonitor();
	server.ShutDown();
	server.Close();
	}