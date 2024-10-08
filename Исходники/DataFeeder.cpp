int main(int argc, char* argv[])
{
	pthread_mutex_t  mutex_lock = PTHREAD_MUTEX_INITIALIZER;

	// Check parameter
	if (argc < 2)
	{
	  cout << "You have to provide the input data file name as a commad line argument." << endl;
	  return 0;

	}

	char* dataFile = argv[1];
        int64_t eventCnt = 0;

	//CLRDataProvider
	CLRDataProvider* provider = new CLRDataProvider();
	
	//Initialize the provider
	cout << "Initializing..." << endl;
	int ret = provider->Initialize(dataFile, 10000, &mutex_lock);

	//Allocate caller's buffer
	if ( ret != SUCCESS )
	  {	
	    ErrorHandler(ret);
	    return 0;

	  }
	else
	{
		//Using the provider
		if( provider->PrepareData(provider) == SUCCESS )
		{
			int		nTuplesRead = 0;
			int		nMaxTuples  = 100;
			LPTuple lpTuples = new LRTuple[nMaxTuples ];
			
			int seconds = 0;
			long emittedCarEventsCnt = 0;

			for(;;) {
				// Get a random number between 5 and 15
				srand(time(NULL));
				int s =  (int) ((((double) rand())/ RAND_MAX) * 10) + 5;

				// Sleep s seconds
				sleep(s);
				int ret;
			  
				for(;;) {
					//Gets available data
					ret = provider->GetData(lpTuples, nMaxTuples, nTuplesRead);

					if ( ret < 0 ) {
						//Handle erros including eof
						ErrorHandler(ret);
						break;
					}

					if ( nTuplesRead == 0 ) {
						//No tuple available
						break;
					}
					
					//Using the return data
					for(int i = 0; i < nTuplesRead; i++ ) {
						eventCnt++;

						// Always print the very first event.
						// After that, print only once for every 500K events.
						if ((eventCnt == 1ul) || ((eventCnt % 500000ul) == 0ul))  {
					 		time_t now = time(0);
					 		struct tm  tstruct;
					 		char       buf[80];
					 		tstruct = *localtime(&now);
					 		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
					 		char* str =  lpTuples[i].ToString();
					 		cout << string(buf) << "     " << eventCnt << "-->" << str << endl;
					 		delete str;
						}

					 	emittedCarEventsCnt++;
					}

					if ( nTuplesRead < nMaxTuples ) 
					{
						//Last tuple has been read
						break;
					}
				}

				if ( ret < SUCCESS )
				{				
					break;
				}

				seconds += s;
				cout << seconds << " seconds have passed. Number of car events emitted=" << emittedCarEventsCnt << endl;
			}
		}
		
		//Uninitialize the provider
		cout << "Uninitialize..." << endl;
		provider->Uninitialize();
	}

	delete provider;
	
	return 0;
}