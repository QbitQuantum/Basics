UINT COXFileWatcher::FileWatchThreadFunction(LPVOID pParam)
// --- In  : pParam: a pointer to the current COXFileWatcher object 
	// --- Out : 
	// --- Returns :
	// --- Effect : Used as a worker thread function
{
#if defined (_WINDLL)
#if defined (_AFXDLL)
	AFX_MANAGE_STATE(AfxGetAppModuleState());
#else
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#endif

	ASSERT(pParam!=NULL);

	COXFileWatcher* pThis=(COXFileWatcher*)pParam;
	HANDLE*			pHandles=pThis->m_pHandles;
	
	pThis->m_bThreadIsRunning = TRUE;

	VERIFY(pThis->m_eventStartThread.SetEvent());

#if defined(_UNICODE) && (_WIN32_WINNT >= 0x400)
// Extended info is supported

	static TCHAR	szFileName[_MAX_PATH];
	// --- the name of the file if extended info is available
	static TCHAR	szNewFileName[_MAX_PATH];
	// --- the name of the new file if extended info is available and action is rename
	
	FILE_NOTIFY_INFORMATION* pfnInfo=NULL;
	// -- pointer to a buffer with extended information (if available)

#endif // defined(_UNICODE) && (_WIN32_WINNT >= 0x400)

	COXFileWatchNotifier* pfwnNotifier;
	// --- the notifier object that will be posted/sended

	DWORD nCount=PtrToLong(pThis->m_arWatchedDirs.GetSize()+1);
	
	// Exit from the loop only when the StartStopEvent as signaled
	while(TRUE)
	{
		DWORD dwRetValue = WaitForMultipleObjects(nCount, pHandles, 
			FALSE, INFINITE);

		// Check for error
		if(dwRetValue == WAIT_FAILED || dwRetValue<WAIT_OBJECT_0 || 
			dwRetValue > (WAIT_OBJECT_0 + nCount - 1))
		{
			pThis->m_hrError = HRESULT_FROM_WIN32(::GetLastError());
			break;
		}
		else  
		{
			// To stop the thread or a notification is signaled
			if(dwRetValue == WAIT_OBJECT_0)
			{
				VERIFY(pThis->m_mxThreadShouldStop.Unlock());
				// Informs the main thread that we are waiting
//				VERIFY(pThis->m_mxThreadStopped.Unlock());
				pThis->m_mxThreadStopped.Unlock();
				// Wait for the main thread
				VERIFY(pThis->m_mxThreadCanContinue.Lock());
				VERIFY(pThis->m_mxThreadStopped.Lock());
				VERIFY(pThis->m_mxThreadCanContinue.Unlock());

				// In this point the main thread should prepare the handles

				if(pThis->m_pNewHandles==NULL) 
				{
					break; // Stops the thread
				}

				// Set new handles
				pHandles=pThis->m_pNewHandles;
				nCount = PtrToLong(pThis->m_arWatchedDirs.GetSize()+1);

				continue;
			}
			else
			{ 
				// ... OK. New notification

				//if notification comes in the period of the time
				//that this thread is to be deleted, so do not
				//process the notification.
				if (pThis->m_bDeletingThread)
					break;
				
				// Find the directory entry
				int nSignaledPath=dwRetValue-WAIT_OBJECT_0-1;
				
				COXWatchedDir* pwdPath = (pThis->m_arWatchedDirs)[nSignaledPath];

#if defined(_UNICODE) && (_WIN32_WINNT >= 0x400)
// Extended info is supported
				DWORD dwNumberOfBytesTransferred;
				BOOL bValid;

				if(pwdPath->m_bExtended)
				{
					// ... OK. We have extended info. Take a pointer to it.
					pfnInfo=(FILE_NOTIFY_INFORMATION*)pwdPath->m_lpBuffer;

					// ... we have to check if the notification is valid or not
					// The check must be done before FindNextHandle()
					bValid= ::GetOverlappedResult(pwdPath->m_hDirectory,      // handle of the directory
								  				  pwdPath->m_pOverlapped,	  // address of overlapped structure 
 												  &dwNumberOfBytesTransferred, // address of actual bytes count 
												  FALSE);					  /// wait flag 

					if(bValid == FALSE || dwNumberOfBytesTransferred == 0) 
					{
						// Something is wrong
#ifdef _DEBUG
						if(bValid == FALSE)
						{
							pThis->m_hrError = HRESULT_FROM_WIN32(::GetLastError());
							CONDITIONAL_TRACE_RESULT("COXFileWatcher::FileWatchThreadFunction", pThis->m_hrError)
						}
						else // dwNumberOfBytesTransferred == 0
						{
							TRACE(_T("\nThe buffer passed to ReadDirectoryChangesW() is too small!\n"));
						}
#endif // _DEBUG

						// ... update the handle
						if(!pwdPath->FindNextHandle((pThis->m_pHandles)[nSignaledPath+1]))
						{
							pThis->m_hrError=
								HRESULT_FROM_WIN32(::GetLastError());
							break;
						}

						// The extended information is available, but it is not valid
						continue;
					}
				}

				while(TRUE)
				{
					if(pwdPath->m_bExtended)
					{
						// Extended information is available
						memcpy(szFileName,(LPCTSTR)&pfnInfo->FileName[0], 
							pfnInfo->FileNameLength);
						szFileName[pfnInfo->
							FileNameLength/sizeof(TCHAR)]=_T('\0');

						if(pfnInfo->Action == FILE_ACTION_RENAMED_OLD_NAME) 
						{
							pfnInfo=(FILE_NOTIFY_INFORMATION*)(((char*)pfnInfo)+
								pfnInfo->NextEntryOffset);
							memcpy(szNewFileName, (LPCTSTR)&pfnInfo->FileName[0],
								pfnInfo->FileNameLength);
							szNewFileName[pfnInfo->
								FileNameLength/sizeof(TCHAR)]=_T('\0');
						}
						else
						{
							szNewFileName[0]=_T('\0');
						}
						pfwnNotifier= new COXFileWatchNotifier(pwdPath->m_sPath,
							pwdPath->m_bWatchSubTree,pwdPath->m_dwWatchFilter, 
							TRUE,pfnInfo->Action,szFileName,szNewFileName);
					}
					else
#endif // defined(_UNICODE) && (_WIN32_WINNT >= 0x400)
					{
						// ... there is no extended information
						pfwnNotifier= new COXFileWatchNotifier(pwdPath->m_sPath,
							pwdPath->m_bWatchSubTree,pwdPath->m_dwWatchFilter, 
							FALSE,0,NULL,NULL);
					}

					// Notify the derived class or ...
					if(!pThis->OnNotify(*pfwnNotifier) && 
						pwdPath->m_hwndWindowToNotify!=NULL)
					{
						// ... post/send message
						UINT nItemIndex=pThis->m_arFileWatchNotifiers.
							AddItem(pfwnNotifier);
						if(pwdPath->m_bPost)
						{
							::PostMessage(pwdPath->m_hwndWindowToNotify, 
								WM_OX_FILE_NOTIFY,nItemIndex,LPARAM(0));
						}
						else
						{
							::SendMessage(pwdPath->m_hwndWindowToNotify, 
								WM_OX_FILE_NOTIFY,nItemIndex,LPARAM(0));
						}
					}
					else 
					{
						// the notifier object is not queued so delete it
						delete pfwnNotifier;
					}

#if defined(_UNICODE) && (_WIN32_WINNT >= 0x400)
// Extended info is supported
					if(!pwdPath->m_bExtended || pfnInfo->NextEntryOffset == 0) 
					{
						break;
					}
					else
					{
						// ... go to the next entry in the buffer...
						pfnInfo = (FILE_NOTIFY_INFORMATION*)(((char*)pfnInfo)+
							pfnInfo->NextEntryOffset);
					}
				} // while(TRUE);

#endif // defined(_UNICODE) && (_WIN32_WINNT >= 0x400)

				// ... update the handle
				if(!pwdPath->FindNextHandle((pThis->m_pHandles)[nSignaledPath+1]))
				{
					pThis->m_hrError = HRESULT_FROM_WIN32(::GetLastError());
					break;
				}

			}