void COpcAdapter::Cycle()
{
	GLogger.LogMessage(StdStringFormat("COpcAdapter::Cycle() for IP = %s\n",_device.c_str()));
	HRESULT hr;
	int nHeartbeat=0;

	_set_se_translator( trans_func );  // correct thread?
	CoInitialize(NULL);

	hr = ::CoInitializeSecurity( NULL, //Points to security descriptor 
		-1, //Count of entries in asAuthSvc 
		NULL, //Array of names to register 
		NULL, //Reserved for future use 
		RPC_C_AUTHN_LEVEL_NONE, //The default authentication //level for proxies 
		RPC_C_IMP_LEVEL_IDENTIFY, //The default impersonation //level for proxies 
		NULL, //Reserved; must be set to  NULL
		EOAC_NONE, //Additional client or //server-side capabilities 
		NULL //Reserved for future use 
		);  
	_set_se_translator( trans_func );  // doesn't seem required.
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	ReadOPCSettings();
	if(_opcservermachine=="127.0.0.1"|| (stricmp(_opcservermachine.c_str(),"localhost")==0))
		_opcservermachine.clear();

	::Sleep(1000);
	//boost::mutex::scoped_lock lock(_access);
	//this->_agentconfig->cond.wait(lock);


	_mRunning=true;

	GLogger.LogMessage(StdStringFormat("COpcAdapter::Cycle() Enter Loop for IP = %s\n",_device.c_str()));
	while(_mRunning)
	{
		try {
			if(FAILED(GatherDeviceData()))
				::Sleep(10*1000);
			::Sleep(_mDelay);
			//SetMTCTagValue("heartbeat", StdStringFormat("%d",nHeartbeat++) );
			SetMTCTagValue("avail", "AVAILABLE" );
		}
		catch(std::exception e)
		{
			GLogger.LogMessage(StdStringFormat("COpcAdapter::Cycle() exception - %s \n", e.what()), INFO);
		}
		catch(...)
		{
			GLogger.LogMessage(StdStringFormat("COpcAdapter::Cycle() exception  \n"), INFO);
		}
	}
	::CoUninitialize();
}