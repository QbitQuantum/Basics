    void Listener::initAndListen() {
        checkTicketNumbers();
        vector<SOCKET> socks;
        
        {
            vector<SockAddr> mine = ipToAddrs(_ip.c_str(), _port, false);
            if ( ! _setupSockets( mine , socks ) )
                return;
        }

#ifdef MONGO_SSL
        _logListen(_port, _ssl);
#else
        _logListen(_port, false);
#endif
                
        OwnedPointerVector<EventHolder> eventHolders;
        boost::scoped_array<WSAEVENT> events(new WSAEVENT[socks.size()]);
        
        
        // Populate events array with an event for each socket we are watching
        for (size_t count = 0; count < socks.size(); ++count) {
            EventHolder* ev(new EventHolder);
            eventHolders.mutableVector().push_back(ev);
            events[count] = ev->get();            
        }
            
        while ( ! inShutdown() ) {
            // Turn on listening for accept-ready sockets
            for (size_t count = 0; count < socks.size(); ++count) {
                int status = WSAEventSelect(socks[count], events[count], FD_ACCEPT | FD_CLOSE);
                if (status == SOCKET_ERROR) {
                    const int mongo_errno = WSAGetLastError();
                    error() << "Windows WSAEventSelect returned " 
                        << errnoWithDescription(mongo_errno) << endl;
                    fassertFailed(16727);
                }
            }
        
            // Wait till one of them goes active, or we time out
            DWORD result = WSAWaitForMultipleEvents(socks.size(), 
                                                    events.get(), 
                                                    FALSE, // don't wait for all the events
                                                    10, // timeout, in ms 
                                                    FALSE); // do not allow I/O interruptions
            if (result == WSA_WAIT_FAILED) {
                const int mongo_errno = WSAGetLastError();
                error() << "Windows WSAWaitForMultipleEvents returned " 
                    << errnoWithDescription(mongo_errno) << endl;
                fassertFailed(16723);
            }
        
            if (result == WSA_WAIT_TIMEOUT) {
                _elapsedTime += 10;
                continue;
            }
            _elapsedTime += 1; // assume 1ms to grab connection. very rough
            
            // Determine which socket is ready
            DWORD eventIndex = result - WSA_WAIT_EVENT_0;
            WSANETWORKEVENTS networkEvents;            
            // Extract event details, and clear event for next pass
            int status = WSAEnumNetworkEvents(socks[eventIndex], 
                                              events[eventIndex], 
                                              &networkEvents);
            if (status == SOCKET_ERROR) {
                const int mongo_errno = WSAGetLastError();
                error() << "Windows WSAEnumNetworkEvents returned " 
                    << errnoWithDescription(mongo_errno) << endl;
                continue;
            }
            
            if (networkEvents.lNetworkEvents & FD_CLOSE) {              
                log() << "listen socket closed" << endl;
                break;
            }
            
            if (!(networkEvents.lNetworkEvents & FD_ACCEPT)) {
                error() << "Unexpected network event: " << networkEvents.lNetworkEvents << endl;
                continue;
            }
            
            int iec = networkEvents.iErrorCode[FD_ACCEPT_BIT];
            if (iec != 0) {                 
                error() << "Windows socket accept did not work:" << errnoWithDescription(iec) 
                        << endl;
                continue;
            }
            
            status = WSAEventSelect(socks[eventIndex], NULL, 0);                
            if (status == SOCKET_ERROR) {
                const int mongo_errno = WSAGetLastError();
                error() << "Windows WSAEventSelect returned " 
                    << errnoWithDescription(mongo_errno) << endl;
                continue;
            }
            
            disableNonblockingMode(socks[eventIndex]);
            
            SockAddr from;
            int s = accept(socks[eventIndex], from.raw(), &from.addressSize);
            if ( s < 0 ) {
                int x = errno; // so no global issues
                if ( x == ECONNABORTED || x == EBADF ) {
                    log() << "Listener on port " << _port << " aborted" << endl;
                    return;
                }
                if ( x == 0 && inShutdown() ) {
                    return;   // socket closed
                }
                if( !inShutdown() ) {
                    log() << "Listener: accept() returns " << s << " " 
                        << errnoWithDescription(x) << endl;
                    if (x == EMFILE || x == ENFILE) {
                        // Connection still in listen queue but we can't accept it yet
                        error() << "Out of file descriptors. Waiting one second before"
                            " trying to accept more connections." << warnings;
                        sleepsecs(1);
                    }
                }
                continue;
            }
            if (from.getType() != AF_UNIX)
                disableNagle(s);

            long long myConnectionNumber = globalConnectionNumber.addAndFetch(1);

            if ( _logConnect && ! cmdLine.quiet ){
                int conns = globalTicketHolder.used()+1;
                const char* word = (conns == 1 ? " connection" : " connections");
                log() << "connection accepted from " << from.toString() << " #" << myConnectionNumber << " (" << conns << word << " now open)" << endl;
            }
            
            boost::shared_ptr<Socket> pnewSock( new Socket(s, from) );
#ifdef MONGO_SSL
            if (_ssl) {
                pnewSock->secureAccepted(_ssl);
            }
#endif
            accepted( pnewSock , myConnectionNumber );
        }
    }