int SelEpolKqEvPrt::getEvents()
{
	int numEvents = -1;
	#if defined(USE_WIN_IOCP)
		#ifdef OS_MINGW_W64
			IOOverlappedEntry entries[64];
			ULONG nEvents = 0;
			if(!GetQueuedCompletionStatusEx(iocpPort,
						(OVERLAPPED_ENTRY*)entries,
						64,
	                    &nEvents,
						(DWORD)this->timeoutMilis,
						FALSE)) {
				int errCd = WSAGetLastError();
				if(errCd != WAIT_TIMEOUT)
				{
					std::cout << "Error occurred during GetQueuedCompletionStatusEx " << WSAGetLastError() << std::endl;
				}
	           	return -1;
	        }
			psocks.clear();
			for(long i = 0; i < (long)nEvents; i++) {
				DWORD qty;
				DWORD flags;
				if(WSAGetOverlappedResult(entries[i].o->sock, (LPWSAOVERLAPPED)entries[i].o, &qty, FALSE, &flags))
				{
					psocks.push_back(entries[i].o);
				}
			}
			return (int)psocks.size();
		#else
			OVERLAPPED       *pOverlapped = NULL;
			IOOperation *lpContext = NULL;
			DWORD            dwBytesTransfered = 0;
			BOOL bReturn = GetQueuedCompletionStatus(iocpPort,
								&dwBytesTransfered,
								(LPDWORD)&lpContext,
								&pOverlapped,
								(DWORD)this->timeoutMilis);
			if (FALSE == bReturn)
			{
				return -1;
			}
			IOOperation* iops = (IOOperation*)lpContext;
			psocks.clear();
			psocks.push_back(iops);
			return 1;
		#endif
	#elif defined(USE_MINGW_SELECT)
		readfds = master;
		if(timeoutMilis>1)
		{
			struct timeval tv;
			tv.tv_sec = (timeoutMilis/1000);
			tv.tv_usec = (timeoutMilis%1000)*1000;
			numEvents = select(fdMax+1, &readfds, NULL, NULL, &tv);
		}
		else
		{
			numEvents = select(fdMax+1, &readfds, NULL, NULL, NULL);
		}
		if(numEvents==-1)
		{
			perror("select()");
		}
		else
		{
			if(fdMax>0)
				return fdMax+1;
		}
	#elif defined(USE_SELECT)
		for (int var = 0; var < fdsetSize; ++var) {
			readfds[var] = master[var];
		}
		if(timeoutMilis>1)
		{
			struct timeval tv;
			tv.tv_sec = (timeoutMilis/1000);
			tv.tv_usec = (timeoutMilis%1000)*1000;
			numEvents = select(fdMax+1, readfds, NULL, NULL, &tv);
		}
		else
		{
			numEvents = select(fdMax+1, readfds, NULL, NULL, NULL);
		}
		if(numEvents==-1)
		{
			perror("select()");
		}
		else
		{
			if(fdMax>0)
				return fdMax+1;
		}
	#elif defined USE_EPOLL
		int ccfds = curfds;
		if(curfds<=0) {
			ccfds = 1;
		}
		numEvents = epoll_wait(epoll_handle, events, ccfds+1, timeoutMilis);
	#elif defined USE_KQUEUE
		if(timeoutMilis>1)
		{
			struct timespec tv;
			tv.tv_sec = (timeoutMilis/1000);
			tv.tv_nsec = (timeoutMilis%1000)*1000000;
			numEvents = kevent(kq, NULL, 0, evlist, MAXDESCRIPTORS, &tv);
		}
		else
		{
			numEvents = kevent(kq, NULL, 0, evlist, MAXDESCRIPTORS, NULL);
		}
	#elif defined USE_DEVPOLL
		struct dvpoll pollit;
		pollit.dp_timeout = timeoutMilis;
		pollit.dp_nfds = curfds;
		pollit.dp_fds = polled_fds;
		numEvents = ioctl(dev_poll_fd, DP_POLL, &pollit);
	#elif defined USE_EVPORT
		uint_t nevents, wevents = 0;
		if(timeoutMilis>1)
		{
			struct timespec tv
			tv.tv_sec = (timeoutMilis/1000);
			tv.tv_nsec = (timeoutMilis%1000)*1000000;
			//uint_t num = 0;
			if (port_getn(port, evlist, 0, &wevents, &tv) < 0) return 0;
			if (0 == wevents) wevents = 1;
			nevents = wevents;
			if (port_getn(port, evlist, (uint_t) MAXDESCRIPTORS, &nevents, &tv) < 0) return 0;
		}
		else
		{
			//uint_t num = 0;
			if (port_getn(port, evlist, 0, &wevents, NULL) < 0) return 0;