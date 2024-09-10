DWORD WINAPI Store(LPVOID lpParam) {
	
	//initialize the pseudorandom numbers generator
	unsigned int seed;
	seed = (unsigned int)time(NULL);
	srand(seed);
	
	//create message queue and signalize
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	
	if (!SetEvent(ghStoreQueueEvent)) {
		return (EXIT_FAILURE);
	}
	
	//waiting until transporter thread create message queue
	WaitForSingleObject(ghTransporterQueueEvent, INFINITE);
	
	//message loop
	BOOL bRet;
	int fuelWeight;
	
	while (TRUE) {
		
		//check terminate flag
		if (terminate) {
			break;
		}
		
		//calculate fuel weight
		//it has mass range from 1 to maxLoad
		fuelWeight = rand() % maxLoad + 1;
		
		//visualisation of production of the fuel
		for (int i = 0; i < fuelWeight; ++i) {
			delay(SUSPEND_FACT * 2);
			setfillstyle(1, cGREY);
			bar(10, 235 - i * 25, 70, 255 - i * 25);
		}
		
		//wait the transporter
		if ((bRet = GetMessage(&msg,				//pointer to MSG structure
							NULL, 					//retrive messages from any windows belong this thread
							WM_TRANSPORT_EMPTY, 	//message filtering
							WM_TRANSPORT_EMPTY)) 
		== 0) {
			//WM_QUIT arrived
			//terminate the thread
			break;
		}
		else if (bRet == -1) {
			//handle error
			return (EXIT_FAILURE);
		}
		else {
			//load the fuel to the transporter
			//visualisation of load process
			for (int i = maxLoad - fuelWeight; i < maxLoad; ++i) {
				delay(SUSPEND_FACT / 2);
				setfillstyle(1, cWHITE);
				bar(10, i * 25 + 10, 70, i * 25 + 30);
			}
			//post the message
			if (PostThreadMessage(dwThreadTransporterId, 	//message for transporter thread
							WM_FUEL_LOADING, 				//message type
							0,								//no WPARAM
							(LPARAM)fuelWeight) 			//pass fuel weight as LPARAM
			== 0) {
				//handle error
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}