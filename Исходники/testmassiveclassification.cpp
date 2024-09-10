int testmassiveclassification::execute()
{
	if (!MVTApp::startStore()) {mLogger.print("Failed to start store\n"); return RC_NOACCESS;}
	mSession = MVTApp::startSession();
	mLargeClass=0;

	if(mpArgs->get_param("largeclass",mLargeClass))
	{
		if(mLargeClass>COUNT_CLASS)
		{
			mLogger.out()<<"Invalid parameter value. -largeclass should not be greater than "<<COUNT_CLASS<<"running with default values";
			mLargeClass=0;
		}
		mLogger.out()<<endl<<mLargeClass<<" classes will have all the pins";
	}
	
	createProps(COUNT_PROP);
	defineClasses(COUNT_CLASS);
	createPins(COUNT_PIN);
	printResults();

	mSession->terminate();
	MVTApp::stopStore();
	return RC_OK;
}