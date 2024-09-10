void ServerThread::Resume() {
#ifdef _WIN32
    threadHandle = (HANDLE)_beginthreadex(NULL, 0, ExecuteServerThread, this, 0, &threadId);
    if(threadHandle == 0) {
#else
    int iRet = pthread_create(&threadId, NULL, ExecuteServerThread, this);
    if(iRet != 0) {
#endif
		AppendDebugLog("%s - [ERR] Failed to create new ServerThread\n", 0);
    }
}
//---------------------------------------------------------------------------

void ServerThread::Run() {
    bActive = true;
#ifdef _WIN32
    SOCKET s;
#else
	int s;
#endif
    sockaddr_storage addr;
	socklen_t len = sizeof(addr);

#ifndef _WIN32
    struct timespec sleeptime;
    sleeptime.tv_sec = 0;
    sleeptime.tv_nsec = 1000000;
#endif

	while(bTerminated == false) {
		s = accept(server, (struct sockaddr *)&addr, &len);

		if(iSuspendTime == 0) {
			if(bTerminated == true) {
#ifdef _WIN32
				if(s != INVALID_SOCKET)
					shutdown(s, SD_SEND);
                        
				closesocket(s);
#else
                if(s != -1)
                    shutdown(s, SHUT_RDWR);
                        
				close(s);
#endif
				continue;
			}

#ifdef _WIN32
			if(s == INVALID_SOCKET) {
				if(WSAEWOULDBLOCK != WSAGetLastError()) {
#else
            if(s == -1) {
                if(errno != EWOULDBLOCK) {
                    if(errno == EMFILE) { // max opened file descriptors limit reached
                        sleep(1); // longer sleep give us better chance to have free file descriptor available on next accept call
                    } else {
#endif
						clsEventQueue::mPtr->AddThread(clsEventQueue::EVENT_SRVTHREAD_MSG, 
                            ("[ERR] accept() for port "+string(ui16Port)+" has returned error.").c_str());
                    }
#ifndef _WIN32
				}
#endif
			} else {
				if(isFlooder(s, addr) == true) {
#ifdef _WIN32
					shutdown(s, SD_SEND);
					closesocket(s);
#else
                    shutdown(s, SHUT_RDWR);
                    close(s);
#endif
				}

#ifdef _WIN32
				::Sleep(1);
#else
                nanosleep(&sleeptime, NULL);
#endif
			}
		} else {
			uint32_t iSec = 0;
			while(bTerminated == false) {
				if(iSuspendTime > iSec) {
#ifdef _WIN32
					::Sleep(1000);
#else
					sleep(1);
#endif
					if(bSuspended == false) {
						iSec++;
					}
					continue;
				}

#ifdef _WIN32
				EnterCriticalSection(&csServerThread);
#else
				pthread_mutex_lock(&mtxServerThread);
#endif
				iSuspendTime = 0;
#ifdef _WIN32
				LeaveCriticalSection(&csServerThread);
#else
				pthread_mutex_unlock(&mtxServerThread);
#endif

				if(Listen(true) == true) {
					clsEventQueue::mPtr->AddThread(clsEventQueue::EVENT_SRVTHREAD_MSG, 
						("[SYS] Server socket for port "+string(ui16Port)+" sucessfully recovered from suspend state.").c_str());
				} else {
					Close();
				}
				break;
			}
		}
	}

    bActive = false;
}
//---------------------------------------------------------------------------

void ServerThread::Close() {
    bTerminated = true;
#ifdef _WIN32
	closesocket(server);
#else
    shutdown(server, SHUT_RDWR);
	close(server);
#endif
}
//---------------------------------------------------------------------------

void ServerThread::WaitFor() {
#ifdef _WIN32
    WaitForSingleObject(threadHandle, INFINITE);
#else
	if(threadId != 0) {
		pthread_join(threadId, NULL);
        threadId = 0;
	}
#endif
}