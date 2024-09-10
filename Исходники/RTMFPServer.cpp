void RTMFPServer::run() {

	try {
		_startDatetimeStr = DateTimeFormatter::format(LocalDateTime(), "%b %d %Y %H:%M:%S");
		_pSocket->bind(SocketAddress("0.0.0.0",_port));
		NOTE("RTMFP server sendbufsize %d recvbufsize %d recvtmo %d sendtmo %d", 
				_pSocket->getSendBufferSize(),
				_pSocket->getReceiveBufferSize(),
				_pSocket->getReceiveTimeout().milliseconds(),
				_pSocket->getSendTimeout().milliseconds()
				);

		sockets.add(*_pSocket,*this);  //_mainSockets
		NOTE("RTMFP server starts on %u port",_port);

		if(_shellPort > 0) { 
			_shellSocket.bind(SocketAddress("0.0.0.0", _shellPort));
			sockets.add(_shellSocket, *this);
			NOTE("RTMFP server shell command portal on %u prot", _shellPort);
		}

		onStart();

		RTMFPManager manager(*this);
		bool terminate=false;
		while(!terminate)
			handle(terminate);

	} catch(Exception& ex) {
		FATAL("RTMFPServer, %s",ex.displayText().c_str());
	} catch (exception& ex) {
		FATAL("RTMFPServer, %s",ex.what());
	} catch (...) {
		FATAL("RTMFPServer, unknown error");
	}

	sockets.remove(*_pSocket); // _mainSockets

	// terminate handle
	terminate();
	
	// clean sessions, and send died message if need
	_handshake.clear();
	_sessions.clear();

	// stop receiving and sending engine (it waits the end of sending last session messages)
	poolThreads.clear();

	// close UDP socket
	_pSocket->close();

	// close shell command port 
	if(_shellPort > 0) { 
		_shellSocket.close();
	}

	sockets.clear();
	//_mainSockets.clear();
	_port=0;
	onStop();

	if(_pCirrus) {
		delete _pCirrus;
		_pCirrus = NULL;
	}

	if(_pSocket) {
		delete _pSocket;
		_pSocket = NULL;
	}
	
	NOTE("RTMFP server stops");
}