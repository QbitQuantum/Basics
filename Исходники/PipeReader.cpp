DWORD PipeReader::startServer() {
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = FALSE;  
	CreateMyDACL(&sa);

	wchar_t temp[300];
	swprintf(temp,L"\\\\.\\pipe\\%s",pipeName);
	HANDLE _pipe=CreateNamedPipe(temp,PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,PIPE_TYPE_BYTE,PIPE_UNLIMITED_INSTANCES,0,0,0,&sa);
	swprintf(temp,L"\\\\.\\pipe\\%s",pipeEventName);
	HANDLE _eventpipe=CreateNamedPipe(temp,PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,PIPE_TYPE_BYTE,PIPE_UNLIMITED_INSTANCES,0,0,0,&sa);
	wchar_t log[300];
	swprintf(log,L"[BixVReader]Pipe created:%s:%08Ix",pipeName,_pipe);
	OutputDebugString(log);

	while (true) {
		//__try {
			BOOL ris=ConnectNamedPipe(_pipe,NULL);
			if (ris==0) {
				swprintf(log,L"[BixVReader]Pipe NOT connected:%x",GetLastError());
				OutputDebugString(log);
			}
			else {
				swprintf(log,L"[BixVReader]Pipe connected");
				OutputDebugString(log);
				}
			ris=ConnectNamedPipe(_eventpipe,NULL);
			if (ris==0) {
				swprintf(log,L"[BixVReader]Event Pipe NOT connected:%x",GetLastError());
				OutputDebugString(log);
			}
			else {
				swprintf(log,L"[BixVReader]Event Pipe connected");
				OutputDebugString(log);
			}
			pipe=_pipe;
			eventpipe=_eventpipe;
			if (waitInsertIpr!=NULL) {
				SectionLocker lock(device->m_RequestLock);
				// if I'm waiting for card insertion, verify if there's a card present
				if (initProtocols()) {
					if (waitInsertIpr->UnmarkCancelable()==S_OK)
						waitInsertIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					waitInsertIpr=NULL;
					state=SCARD_SWALLOWED;					
				}
			}
			
			while (true) {
				// wait for a command
				DWORD command=0;
				DWORD read=0;
				if (!ReadFile(eventpipe,&command,sizeof(DWORD),&read,NULL)) {
					state=SCARD_ABSENT;
					OutputDebugString(L"[BixVReader]Pipe error");
					powered=0;
					pipe=NULL;
					eventpipe=NULL;
					if (waitRemoveIpr!=NULL) {// card inserted
						SectionLocker lock(device->m_RequestLock);
						OutputDebugString(L"[BixVReader]complete Wait Remove");
						if (waitRemoveIpr->UnmarkCancelable()==S_OK) {
							OutputDebugString(L"[BixVReader]Wait Remove Unmarked");
							waitRemoveIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
							OutputDebugString(L"[BixVReader]Wait Remove Completed");
						}
						waitRemoveIpr=NULL;
					}
					if (waitInsertIpr!=NULL) {// card removed
						SectionLocker lock(device->m_RequestLock);
						OutputDebugString(L"[BixVReader]cancel Wait Remove");
						if (waitInsertIpr->UnmarkCancelable()==S_OK) {
							OutputDebugString(L"[BixVReader]Wait Insert Unmarked");
							waitInsertIpr->CompleteWithInformation(HRESULT_FROM_WIN32(ERROR_CANCELLED), 0);
							OutputDebugString(L"[BixVReader]Wait Insert Cancelled");
						}
						waitInsertIpr=NULL;
					}
					DisconnectNamedPipe(_pipe);
					DisconnectNamedPipe(_eventpipe);
					break;
				}
				OutputDebugString(L"[BixVReader]Pipe data");
				if (command==0)
					powered=0;
				if (command==0 && waitRemoveIpr!=NULL) {// card removed
					SectionLocker lock(device->m_RequestLock);
					state=SCARD_ABSENT;
					if (waitRemoveIpr->UnmarkCancelable()==S_OK) {						
						waitRemoveIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					}
					waitRemoveIpr=NULL;
				}
				else if (command==1 && waitInsertIpr!=NULL) {// card inserted
					SectionLocker lock(device->m_RequestLock);
					state=SCARD_SWALLOWED;
					initProtocols();
					if (waitInsertIpr->UnmarkCancelable()==S_OK) {
						waitInsertIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					}
					waitInsertIpr=NULL;
				}
			}
		//}
		//__except(EXCEPTION_EXECUTE_HANDLER) {
		//	wchar_t log[300];
		//	DWORD err=GetExceptionCode();
		//	swprintf(log,L"Exception:%08X",err);
		//	OutputDebugString(log);
		//}
	}
	OutputDebugString(L"[BixVReader]Pipe quit!!!");
	return 0;
}