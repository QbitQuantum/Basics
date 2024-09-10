int TestFTIndexRebuild::execute()
{	
	bool lSuccess = true;
	if (MVTApp::startStore())
	{
		ISession *session = MVTApp::startSession();		
		MVTApp::mapStaticProperty(session,"TestFTIndexRebuild.prop1",mPropIds[0]);
		MVTApp::mapStaticProperty(session,"TestFTIndexRebuild.prop2",mPropIds[1]);
		verifyMiscOps(session);
		testFTRebuild(session);
		session->terminate();
		MVTApp::stopStore();
	}
	return lSuccess?0:1;
}