int TestClassMembership::execute()
{
	if (MVTApp::startStore())
	{
		mSession = MVTApp::startSession();
		testDataEvent();		
		testFamilyMembership();
		mSession->terminate();
		MVTApp::stopStore();
	}
	else
	{
		return RC_FALSE;
	}
	return RC_OK;
}