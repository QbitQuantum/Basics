void
Application_InternetExplorer::visitGroup(VisitEvent* visitEvent)
{	

	DWORD *error = NULL;
	
	int n_visited_urls = 0;
	int to_visit = 0;
	int n_visiting = 0;
	int n_urls = visitEvent->getUrls().size();



	IClassFactory* internet_explorer_factory;

	// Get a link to the IE factory for creating IE instances
	HRESULT hr = CoGetClassObject(CLSID_InternetExplorer,
		CLSCTX_LOCAL_SERVER,
		NULL,
		IID_IClassFactory,
		(void**)&internet_explorer_factory); 

	// Allocate on the heap so threads can use the information
	InternetExplorerInstance** iexplore_instances = (InternetExplorerInstance**)malloc(sizeof(InternetExplorerInstance*)*n_urls);
	for(int i = 0; i < n_urls; i++)
	{
		iexplore_instances[i] = new InternetExplorerInstance(internet_explorer_factory);
	}

	VISIT_INFO* visit_information = new VISIT_INFO[n_urls];

	// Loop until all urls have been visited
	while(n_visited_urls < n_urls)
	{
		for(int i = 0; i < MAX_WORKER_THREADS; i++)
		{
			if(!worker_thread_busy[i] && n_visiting < n_urls)
			{
				// Give the threads something to do					
				visit_information[to_visit].internet_explorer_instance = iexplore_instances[to_visit];
				visit_information[to_visit].url = visitEvent->getUrls().at(to_visit);
				worker_thread_data[i] = (LPVOID*)&visit_information[to_visit++];
				worker_thread_busy[i] = true;
				n_visiting++;
				SetEvent(worker_has_data[i]);	
			}
		}

		// Wait for one of the workers threads to finish
		DWORD dwWait = WaitForMultipleObjects(MAX_WORKER_THREADS, worker_finished, false, 60*1000);
		OutputDebugStringA("IE Visit Group Worker Threads Finished.\n");

		// If one has finished then a url has been visited
		int index = dwWait - WAIT_OBJECT_0;
		if(index < MAX_WORKER_THREADS && !worker_thread_busy[index])
		{
			n_visited_urls++;
		}
	}

	// Give the visit event a success or error code based on the visitaion of each url
	for(int i = 0; i < n_urls; i++)
	{
		Url* url = visitEvent->getUrls().at(i);
		visitEvent->setErrorCode(url->getMajorErrorCode());
	}
	OutputDebugStringA("IE Visit Group set errors on urls.\n");

	DWORD errorCode = closeAllInternetExplorers(internet_explorer_factory);
	if(errorCode!=0) {
		visitEvent->setErrorCode( CAPTURE_VISITATION_WARNING );
	}
	OutputDebugStringA("IE Visit Group closed all instances.\n");


	//Delete all IE instance objects
	delete [] visit_information;
	for(int i = 0; i < n_urls; i++)
	{
		delete iexplore_instances[i];
	}
	free(iexplore_instances);
	OutputDebugStringA("IE Visit Group delete IE instances\n");

	// Free the COM interface stuff
	ULONG num_references = internet_explorer_factory->Release();

}