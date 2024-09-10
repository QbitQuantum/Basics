DWORD WINAPI Transporter(LPVOID lpParam) {
	
	HANDLE hPipeClient;
	
	//connected to store pipe as client
	//connect loop
	while (TRUE) {
	
		hPipeClient = CreateFile (
			lpstrStorePipeName,		//pipe name
			GENERIC_READ | 			//read/write access
			GENERIC_WRITE,
			0,						//no sharing
			NULL,					//default security attributes
			OPEN_EXISTING,			//open existing pipe
			0,						//default attributes
			NULL					//no template file
			);
			
		if (hPipeClient != INVALID_HANDLE_VALUE) {
			break;
		}
	}
	
	//pipe connected
	//change to message-read mode
	BOOL fSuccess;
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	
	fSuccess = SetNamedPipeHandleState(
		hPipeClient,				//pipe handle
		&dwMode,					//new pipe mode
		NULL,						//don`t set maximum size
		NULL						//don`t set maximum time
		);
		
	if (!fSuccess) {
		CloseHandle(hPipeClient);
		return (EXIT_FAILURE);
	}
	
	//create pipe for power block threads
	HANDLE hPipe;
	
	hPipe = CreateNamedPipe(
		lpstrTransporterPipeName,		//pipe name
		PIPE_ACCESS_DUPLEX,				//read/write access
		PIPE_TYPE_MESSAGE |				//message type pipe
		PIPE_READMODE_MESSAGE |			//message-read mode
		PIPE_WAIT,						//blocking mode
		1,								//max instances
		cbufsize,						//output buffer size
		cbufsize,						//input buffer size
		0,								//client time-out
		NULL							//default security attributes
	);
	
	if (hPipe == INVALID_HANDLE_VALUE) {
		CloseHandle(hPipeClient);
		return (EXIT_FAILURE);
	}
	
	//general loop
	int fuelWeight = 0;
	int emptyBlock = 0;
	int cap = 0;
	unsigned long cbBytesWrite = 0;
	unsigned long cbBytesRead = 0;
	
	while (TRUE) {
		
		//check terminate flag
		if (terminate) {
			//disconnect client
			FlushFileBuffers(hPipe); 
			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
			//disconnect from server
			CloseHandle(hPipeClient);
			break;
		}
		
		//initial transport position
		setfillstyle(1, cGREY);
		bar(30, 260, 50, 280);
		
		//write to store pipe that transporter is arrived
		//and wait for fuel weight from store
		fSuccess = TransactNamedPipe(
			hPipeClient,		//handle to pipe
			&cap,				//address of write data variable
			cbufsize,			//size of write data variable
			&fuelWeight,		//address of store data variable
			cbufsize,			//size of store data variable
			&cbBytesRead,		//number of bytes read
			NULL				//not overlapped I/O
		);
		
		//transaction is failed
		if (!fSuccess || cbBytesRead == 0) {
			//disconnect client
			FlushFileBuffers(hPipe); 
			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
			//disconnect from server
			CloseHandle(hPipeClient);
			return (EXIT_FAILURE);
		}
		
		//visualisation of loading state
		setfillstyle(1, cGREEN);
		bar(30, 260, 50, 280);
		
		//waiting for the first empty power block
		ConnectNamedPipe(hPipe, NULL);
		
		//take index of empty power block
		fSuccess = ReadFile(
			hPipe, 				//handle to pipe
			&emptyBlock, 		//address of store data variable
			cbufsize, 			//size of store data variable
			&cbBytesRead,		//number of bytes read
			NULL				//not overlapped I/O
			);
		
		//read was failed
		if (!fSuccess || cbBytesRead == 0) {
			//disconnect client
			FlushFileBuffers(hPipe); 
			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
			//disconnect from server
			CloseHandle(hPipeClient);
			return (EXIT_FAILURE);
		}
		
		//visualisation of transferring fuel to appropriate power block
		for (int i = 0; i < emptyBlock * 80 + 80; ++i) {
			setfillstyle(1, cGREEN);
			bar(i + 30, 260, i + 50, 280);
			delay(SUSPEND_FACT / 50);
			setfillstyle(1, cWHITE);
			bar(i + 30, 260, i + 50, 280);
		}
		
		//unload transport position
		setfillstyle(1, cGREEN);
		bar(emptyBlock * 80 + 110, 260, emptyBlock * 80 + 130, 280);
		
		//write that transporter is arrived to power block
		fSuccess = WriteFile(
			hPipe, 					//handle to pipe
			&fuelWeight, 			//address of write data variable
			cbufsize, 				//number of bytes to write
			&cbBytesWrite, 			//number of bytes written
			NULL 					//not overlapped I/O
			);
		
		//write was failed
		if (!fSuccess || cbBytesWrite != cbufsize) {
			//disconnect client
			FlushFileBuffers(hPipe); 
			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
			//disconnect from server
			CloseHandle(hPipeClient);
			return (EXIT_FAILURE);
		}
		
		//waiting until power block is filled
		fSuccess = ReadFile(
			hPipe, 				//handle to pipe
			&cap, 		//address of store data variable
			cbufsize, 			//size of store data variable
			&cbBytesRead,		//number of bytes read
			NULL				//not overlapped I/O
			);
		
		//read was failed
		if (!fSuccess || cbBytesRead == 0) {
			//disconnect client
			FlushFileBuffers(hPipe); 
			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
			//disconnect from server
			CloseHandle(hPipeClient);
			return (EXIT_FAILURE);
		}
		
		//disconnect client
		FlushFileBuffers(hPipe); 
		DisconnectNamedPipe(hPipe);
		
		//visualisation of transferring back to store fuel item
		for (int i = emptyBlock * 80 + 80; i >= 0; --i) {
			setfillstyle(1, cGREY);
			bar(i + 30, 260, i + 50, 280);
			delay(SUSPEND_FACT / 100);
			setfillstyle(1, cWHITE);
			bar(i + 30, 260,  i + 50, 280);
		}
	}
	
	return (EXIT_SUCCESS);
}