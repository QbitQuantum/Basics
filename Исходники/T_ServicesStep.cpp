/**
   @SYMTestCaseID T-RApaLsSessionTestStep-TestServiceDiscovery7L
  
   @SYMPREQ 538
  
   @SYMTestCaseDesc Given the size of data that is returned from the server is greater than the default 
   1024 bytes of the buffer, test if a larger buffer is assigned in such cases
   
   @SYMTestPriority 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Call GetAppServicesLC with the app uid as parameter. The size of the resource data in 
   the registration file should be greater than the default size.
   on z: drive.\n
   API Calls:\n	
   RApaLsSession::GetAppServicesLC(TUid aAppUid) const
   
   @SYMTestExpectedResults A larger buffer is allocated. The size of the buffer can be tested by checking 
   the size of the returned data.
    
 */
void CT_ServicesTestStep::TestServiceDiscovery7L()
	{
	INFO_PRINTF1(_L("TestServiceDiscovery7 about to start..."));
	const TUid KUidServerApp = {0x10004c57};
	// get all services for a particular app
	CApaAppServiceInfoArray* array = iApaLsSession.GetAppServicesLC(KUidServerApp);
	TArray<TApaAppServiceInfo> serviceArray(array->Array());
	TInt count = serviceArray.Count();
	TEST(count == 16);
	TPtrC8 opaqueData;
	TInt size(0);
	for(TInt i=0;i<count;i++)
		{
			opaqueData.Set(serviceArray[i].OpaqueData());
			size +=opaqueData.Length(); 
		}
	TEST(size>=1024);
	CleanupStack::PopAndDestroy(array); // the servicearray	
	array = NULL;
	}