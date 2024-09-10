int	TestMultiFT::execute()
{	
	if (MVTApp::startStore())
	{
		mSession =	MVTApp::startSession();
		
		MultiFTSearchContext::sUseStream = false ;
		doTests();
		
		MultiFTSearchContext::sUseStream = true ;
		doTests();		

		mSession->terminate();
		MVTApp::stopStore();
	}
	else
		TVERIFY(false && "Failed to open Store");

	return RC_OK;
}