//on thread can only call putSync once on the callstack.
DSRequest DSRequestQueue::putSync(DSRequest req, BOOL bKeepUIActive)
{	
	HANDLE hEvents[1]; 
	DWORD dwWaitResult;
	int iDebug=0;
	HRESULT hr = S_OK;

	ASSERT(m_pSetRequests);
	if(!m_pSetRequests || !m_dwThreadWorker)
	{
		DSRequest req;
		req.setHR(E_FAIL);
		return req;
	}

	m_pSetRequests->AddRef();
	DSTSSetOfRequests *pSetRequests = m_pSetRequests;

	//not important what this handle is.
	hEvents[0]=m_hThreadWorker;
	ASSERT(hEvents[0]);
	EnterCriticalSection(&m_critsec);
		DSRequest returnValue;		
		
		//put into queue.
		req.putSync(m_dwTotalRequests);		
		put(req);
		
	//leave the critical section so others can put stuff in.		
	LeaveCriticalSection(&m_critsec);	

	//Wait for message to come.
	MSG msg;
	BOOL bRet;
	BOOL bQuit=FALSE;
	
	//
	//Note that we have the possibility of this call stack:
	// putsync (A)
	//    wait for (A).
	//        putsync (B).
	//            wait for (B).
	//                 (A) appears.
	//                 (B) appears.

	CString strMsg = "PutSync threadID:"+str(::GetCurrentThreadId())+"\n";
	TRACE(strMsg);

	DSTSSetOfRequests::FindResult fr;
				
	while(!bQuit)
	{
		dwWaitResult = MsgWaitForMultipleObjects(1,hEvents,FALSE,1000,QS_ALLEVENTS);
	
		if(dwWaitResult==WAIT_TIMEOUT)
			TRACE("PutSync::MsgWait timed out: %i\n", iDebug++);
		else if((dwWaitResult>=WAIT_OBJECT_0) && (dwWaitResult<= (WAIT_OBJECT_0 + 2)))
			TRACE("PutSync::MsgWait got a signal: %i\n", iDebug++);
		else if((dwWaitResult>=WAIT_ABANDONED_0) && (dwWaitResult <= (WAIT_ABANDONED_0 + 2 - 1 )))
			TRACE("PutSync::MsgWait abandoned: %i\n", iDebug++);
		else if((dwWaitResult>=WAIT_IO_COMPLETION) && (dwWaitResult <= (WAIT_IO_COMPLETION + 2 - 1)))
			TRACE("PutSync::MsgWait IO_COMPLETION: %i\n", iDebug++);		
		else if(dwWaitResult==0xFFFFFFFF)
		{
			TRACE("MsgWait failed: %i\n", iDebug++);		
			DWORD dwError = GetLastError();	
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
			    dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,    0,    NULL );
			TRACE((LPTSTR)lpMsgBuf);
			LocalFree( lpMsgBuf );

			//This is caused by the invalid handle of the closed thread. It's okay.
		}
		else ASSERT(0);
		
		bRet = ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
		
		while(bRet && !bQuit)
		{
			bRet = ::GetMessage(&msg, NULL, 0, 0);
			
			ASSERT( (int)bRet != -1 );
			if (bRet)
			{
				if(msg.message==WM_SYNC_CALL_FINISHED)
				{				 			    
					ASSERT(msg.hwnd==NULL);

					DSRequest tempRetvalue;
					tempRetvalue.putSync(msg.wParam);

					//look for a response of ID tempRetValue. This will fill the rest of the struct out.
					fr = pSetRequests->find(tempRetvalue,tempRetvalue);
					if(fr == DSTSSetOfRequests::FR_TERMINATE)
					{
						TRACE("PutSync: The worker thread has terminated. Quiting without waiting for Signal\n.");
						bQuit=TRUE;					
					}
					else if(fr == DSTSSetOfRequests::FR_FOUND)
					{
						if(tempRetvalue==req)
						{
							//the operation is finished.
							bQuit=TRUE;
							
							//TODO: fire off event.
							returnValue=tempRetvalue;
						}
						else
						{
							//it's a different one.
							//check, just in case, if our req is in the map.
							fr = pSetRequests->find(req,returnValue);
							if(fr == DSTSSetOfRequests::FR_TERMINATE)
							{
								TRACE("PutSync: The worker thread has terminated. Quiting without waiting for Signal\n.");
								bQuit=TRUE;
							}
							else if(fr == DSTSSetOfRequests::FR_FOUND)
							{
								//The only time this should happen is below, the case where we're currently in 
								// a dispatch message.
								ASSERT(0);
								pSetRequests->remove(req);
								
								bQuit=TRUE;					
							}
						}
					}
				}
				else
				{
					// TRACE("DSQueue::PutSync: Got a non-queue message: %x.\n", msg.message);
					
					if(bKeepUIActive)
						::DispatchMessage(&msg);
							
					DSRequest outReq;
					//sets returnValue if found.
					fr = pSetRequests->find(req,returnValue);
					if(DSTSSetOfRequests::FR_FOUND == fr)
					{
						pSetRequests->remove(req);
						
						bQuit=TRUE;					
					}
					else if(DSTSSetOfRequests::FR_TERMINATE == fr)
					{
						bQuit=TRUE;					
					}
				}
			}

			bRet = ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);		
		}
	}

	pSetRequests->Release();

	return returnValue;
}	