void NetworkConnection::sendData(const char* data, const int length)
{
	if (!closed && !sendError)	// Ignore call if something is wrong
	{
		// To-do: Make mutex

		// Set send information 
		sendInfo.buf = (char*)data;
		sendInfo.len = length;
			// Make winsock start sending
		if (WSASend(connection, &sendInfo, 1, 
			&bytesSent, 0, &sendOverlapped, NULL) 
				== SOCKET_ERROR)
		{			// If the error returned by the winsock was not a 
					// IO pending error
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				this->sendError = true;	// Set error flag
				// The send error bool makes sure that the close function 
				// doesn't get called before data processing/the current 
				// thread is done, as closing the socket and terminating 
				// the socket could possibly lead to a handfull of 
				// nullreffies during packet processing which could lead 
				// to a lot of null reffernce exceptions.
			}
		}
	}
}