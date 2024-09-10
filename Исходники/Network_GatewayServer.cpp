void RemoteDesktop::GatewayServer::_Run(){

	std::vector<WSAEVENT> EventArray;
	auto socketarray = std::vector<std::shared_ptr<Gateway_Socket>>();
	EventArray.reserve(WSA_MAXIMUM_WAIT_EVENTS);
	socketarray.reserve(WSA_MAXIMUM_WAIT_EVENTS);

	SOCKET listensocket = RemoteDesktop::Listen(_Port, _Host);
	if (listensocket == INVALID_SOCKET) return;

	auto newevent = WSACreateEvent();
	WSAEventSelect(listensocket, newevent, FD_ACCEPT | FD_CLOSE);

	EventArray.push_back(newevent);
	socketarray.push_back(std::make_shared<Gateway_Socket>(listensocket));

	WSANETWORKEVENTS NetworkEvents;
	auto timer = std::chrono::high_resolution_clock::now();
	while (_Running && !EventArray.empty()) {

		auto Index = WSAWaitForMultipleEvents(EventArray.size(), EventArray.data(), FALSE, 1000, FALSE);

		if ((Index != WSA_WAIT_FAILED) && (Index != WSA_WAIT_TIMEOUT) && _Running) {

			WSAEnumNetworkEvents(socketarray[Index]->ThisSocket->socket, EventArray[Index], &NetworkEvents);
			if (((NetworkEvents.lNetworkEvents & FD_ACCEPT) == FD_ACCEPT) && NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == ERROR_SUCCESS){
				if (EventArray.size() >= WSA_MAXIMUM_WAIT_EVENTS - 1) continue;// ignore this event too many connections
				_HandleNewConnect(listensocket, EventArray, socketarray);
			}
			else if (((NetworkEvents.lNetworkEvents & FD_READ) == FD_READ) && NetworkEvents.iErrorCode[FD_READ_BIT] == ERROR_SUCCESS){
				socketarray[Index]->Receive();
			}
			else if (((NetworkEvents.lNetworkEvents & FD_CLOSE) == FD_CLOSE) && NetworkEvents.iErrorCode[FD_CLOSE_BIT] == ERROR_SUCCESS){
				if (Index == 0) {//stop all processing, set running to false and next loop will fail and cleanup
					_Running = false;
					continue;
				}
			}
		}
		//once every second send a keep alive. this will trigger disconnects 
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timer).count() > 1000){
			_CheckForDisconnects(EventArray, socketarray);
			timer = std::chrono::high_resolution_clock::now();
		}
	}
	for (size_t beg = 1; beg < socketarray.size(); beg++){
		//OnDisconnect(sharedrockarray->at(beg));//let all callers know about the disconnect, skip slot 0 which is the listen socket
	}
	//cleanup code here
	for (auto x : EventArray) WSACloseEvent(x);
	DEBUG_MSG("_Listen Exiting");
}