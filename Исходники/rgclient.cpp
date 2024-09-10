int RGClient :: Send (int serverId, unsigned char* sendBuffer, unsigned char*& replyBuffer, int sendLength, int& replyMax) {

	int len;
	LastError = RGOK;
	
	if (serverId <= 0) {

		LastError = RGILLEGALSERVERID;
		return -1;
	}
	
	RGServerPort* port = ServerPortList.GetElementAt (serverId);

	if (port == NULL) {

		LastError = RGSERVERNULL;
		return -1;
	}

	*ServerPid = port->GetServerPid ();
	int status = port->Send (sendLength, sendBuffer);

	if (status < 0) {

		LastError = port->GetLastError ();
		RemoveServer (serverId);
		return -1;
	}

	HANDLE HandleArray [2];
	HandleArray [0] = port->GetServerHandle ();
	HandleArray [1] = OKToReadHandle;

	status = WaitForReadAccess (HandleArray);

	if (status < 0) {

		RemoveServer (serverId);
		return -1;
	}

	len = *Length;

	//
	// Test for buffer overflow...we don't like to encourage this!
	//

	if (len > replyMax) {

		delete[] replyBuffer;
		replyBuffer = new unsigned char [len];
		replyMax = len;
	}

	//
	// Test for continuation
	//

	if (*Type == RGBLOCKINGSEND) {
		
		//
		// No continuation needed
		//	

		memcpy (replyBuffer, DataBegin, len);
		return 0;
	}

	//
	// Need continuation
	//

	Boolean Loop = TRUE;
	unsigned char* CurrentOutputPointer = replyBuffer;
	int WriteSize = BufferSize;
	int LeftToWrite = len;
	Boolean Wait = FALSE;

	while (Loop) {
		
		if (Wait) {
		
			status = WaitForReadAccess (HandleArray);  // wait for continuation clearance

			if (status < 0)
				return status;
		}

		Wait = TRUE;
		memcpy (CurrentOutputPointer, DataBegin, WriteSize);
		CurrentOutputPointer += BufferSize;
		LeftToWrite -= BufferSize;
		HandleArray [1] = ContinuationHandle;

		if ((LeftToWrite <= 0) || (*Type == RGBLOCKINGSEND))
			Loop = FALSE;

		else {

			SetEvent (OKToWriteHandle);
		
			if (LeftToWrite <= BufferSize)
				WriteSize = LeftToWrite;
		}
	}  // end of while loop

	return 0;
}