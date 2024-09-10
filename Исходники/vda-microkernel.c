	void launchKssServiceThread(){
		setContinueKssThread(TRUE);
		setKssServiceThread( (ThreadHandler) _beginthreadex( NULL, 0, &doKssService, NULL, 0, NULL ) );
	}