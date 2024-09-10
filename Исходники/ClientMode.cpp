/*------------------------------------------------------------------------------------------------------------------
--      FUNCTION: udp_deliver_packets
--
--      DATE: Febuary 6 2014
--      REVISIONS: Countless. Most recent, turning it into somewhat reliable UDP.
--
--      DESIGNER: Ramzi Chennafi
--      PROGRAMMER: Ramzi Chennafi
--
--      INTERFACE: void udp_deliver_packets(HWND hwnd, int totalBytesRead, int packet_size, int buffer_count, WSABUF * buffers)
--
--      RETURNS: void
--
--      NOTES:
--      Takes the parent window HWND, the total bytes to be transferred (totalBytesRead), the current packet size, the amount of packets
--		an an array of WSABUFs each containing a packet of data.
--		
--		Delivers the packets over UDP to the specified IP and port, and has some reliability for dropped packets by 
--		incorporating an acknowledgement system as well as a header packet containing the info passed to the function. 
--		If an error occurs in the recvfrom portion of the acknowledgement, consider the transfer dead and restart the program.
--
--		* WILL loop endlessly if the user decides to terminate the server during a transfer. Will continously wait for ACKs.
----------------------------------------------------------------------------------------------------------------------*/
void udp_deliver_packets(HWND hwnd, int totalBytesRead, int packet_size, int buffer_count, WSABUF * buffers){

	SETTINGS * st = (SETTINGS*)GetClassLongPtr(hwnd, 0);
	
	int packets_lost = 0;
	int status;
	char msg[MAX_SIZE];
	DWORD  numBytesSent = 0;
	struct sockaddr_in sin;

	char flags[HEADER_SIZE];
	memset(flags, '\0', HEADER_SIZE);
	sprintf_s(flags, ";%d,%d,%d,%d;", totalBytesRead, packet_size, buffer_count, st->mode);

	LPWSABUF wsaHeaderBuf = (LPWSABUF)malloc(sizeof(WSABUF));
	wsaHeaderBuf->len = HEADER_SIZE;
	wsaHeaderBuf->buf = flags;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(st->client_port));

	if ((sin.sin_addr.s_addr = inet_addr(st->client_send_ip)) == INADDR_NONE)
	{
		activity("Failed to find address\n", EB_STATUSBOX);
		return;
	}
	
	while (1){ // transferring the header packet
		if ((status = WSASendTo(st->client_socket, wsaHeaderBuf, 1, &numBytesSent, 0, (struct sockaddr *)&sin, sizeof(sin), NULL, NULL)) < 0){
			sprintf_s(msg, "Error %d in TCP WSASend(header) with return of %d\n", WSAGetLastError(), status);
			activity(msg, EB_STATUSBOX);
		}

		if (receive_acknowledge(hwnd) == 1) { break; } 
		packets_lost++;
	}
	
	startTime = GetTickCount();

	for (int p = 0; p < buffer_count; p++){
		while (1){ // transferring the actual data
			if ((status = WSASendTo(st->client_socket, &buffers[p], 1, &numBytesSent, 0, (struct sockaddr *)&sin, sizeof(sin), NULL, NULL)) < 0){
				sprintf_s(msg, "Error %d in sendto(buffer) with return of %d\n", WSAGetLastError(), status);
				activity(msg, EB_STATUSBOX);
				return;
			}

			if (receive_acknowledge(hwnd) == 1){ break; }
			packets_lost++;
		}
	}

	endTime = GetTickCount();
	seconds = endTime - startTime;
	sprintf_s(msg, "Data transmission completed in %d milliseconds.\n", seconds);
	activity(msg, EB_STATUSBOX);
}