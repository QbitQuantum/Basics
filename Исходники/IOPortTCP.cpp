//
// Begin accepting a connection to an existing port.  Used by server.
// For synchronous port, blocks until a connection is made (returns TRUE) or an error occurs (returns FALSE).
// For asynchronous port, returns immediately.  Returns TRUE for success or FALSE if any error occurs.
//     Call IsAcceptComplete() to determine if it has completed, and GetAcceptResult() to get result.
//
BOOL PortTCP::Accept()
{
	//
	// Listen to socket.
	//

#if PORT_DETAILS || _DETAILS
	cout << "Listening to socket " << name << "." << endl;
	WSASetLastError(0);
#endif

	if (listen(server_socket, 0) != 0)	// allow at most one connection at a time
	{
		*errmsg << "===> ERROR: Listening to socket " << name << " failed." << endl
		    << "     [PortTCP::Accept() in " << __FILE__ << " line " << __LINE__ << "]" << endl
		    << "     errno = " << WSAGetLastError() << ends;
		OutputErrMsg();
		return FALSE;
	}
	//
	// Accept connections to socket.
	//

#if PORT_DETAILS || _DETAILS
	cout << "Accepting connections to socket " << name << "." << endl;
	WSASetLastError(0);
#endif

	if (synchronous) {
		// don't need any info about who we're talking to
		client_socket = accept(server_socket, NULL, NULL);

		if (client_socket == (int)INVALID_SOCKET) {
			*errmsg << "===> ERROR: Accepting connection to socket " << name << " failed." << endl
			    << "     [PortTCP::Accept() in " << __FILE__ << " line " << __LINE__ << "]" << endl
			    << "     errno = " << WSAGetLastError() << ends;
			OutputErrMsg();
			return FALSE;
		} else {
			return TRUE;
		}
	}
#if defined(IOMTR_OS_WIN32) || defined(IOMTR_OS_WIN64)
	else {
		DWORD bytes_received;

		if (!InitOverlapped(&accept_overlapped)) {
			*errmsg << "===> ERROR: Creating OVERLAPPED structure for socket " << name << " failed." << endl
			    << "     [PortTCP::Accept() in " << __FILE__ << " line " << __LINE__ << "]" << ends;
			OutputErrMsg();
			return FALSE;
		}

		//
		// Create client socket.
		//

#if PORT_DETAILS || _DETAILS
		cout << "Creating client socket for " << name << "." << endl;
		WSASetLastError(0);
#endif

		client_socket = WSASocket(AF_INET, SOCK_STREAM, PF_UNSPEC, NULL, 0, WSA_FLAG_OVERLAPPED);

		if (client_socket == INVALID_SOCKET) {
			*errmsg << "===> ERROR: Creating client socket for " << name << " failed." << endl
			    << "     [PortTCP::Accept() in " << __FILE__ << " line " << __LINE__ << "]" << endl
			    << "     errno = " << WSAGetLastError() << ends;
			OutputErrMsg();
			return FALSE;
		}
		//
		// Accept connections to socket.
		//
		if (AcceptEx(server_socket, client_socket, accept_ex_buffer, 0,	// read no data, only the two addresses, into accept_ex_buffer
			     sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16,
			     &bytes_received, &accept_overlapped)) {
#if PORT_DETAILS || _DETAILS
			cout << "Connection accepted." << endl;
#endif

			return TRUE;
		} else {
			if (WSAGetLastError() == WSA_IO_PENDING)	// Read started OK...
			{
				return TRUE;
			} else {
				*errmsg << "===> ERROR: AcceptEx() failed." << endl
				    << "     [PortTCP::Accept() in " << __FILE__ << " line " << __LINE__ << "]" << ends;
				OutputErrMsg();
				return FALSE;
			}
		}
	}
#elif defined(IOMTR_OS_LINUX) || defined(IOMTR_OS_NETWARE) || defined(IOMTR_OS_OSX) || defined(IOMTR_OS_SOLARIS)
	else {