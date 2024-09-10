/*------------------------------------------------------------------------------------------------------------------
--      FUNCTION: process_header
--
--      DATE: Febuary 6 2014
--      REVISIONS: none
--
--      DESIGNER: Ramzi Chennafi
--      PROGRAMMER: Ramzi Chennafi
--
--      INTERFACE: int process_header(HWND hwnd, SOCKET recv), takes the parent HWND as an argument and the socket the header was sent to.
--
--      RETURNS: void
--
--      NOTES:
--      Retrieves the header datagram from the passed in socket. If using TCP, just grabs it. If on UDP, the header is grabbed then
--		acknowledged. If no header is successfully grabbed, the function is called on every WM_SOCKET message until it is.
----------------------------------------------------------------------------------------------------------------------*/
int process_header(HWND hwnd, SOCKET recv){

	SETTINGS * st = (SETTINGS*)GetClassLongPtr(hwnd, 0);
	DWORD RecvBytes = 0, Flags = 0;
	int status, server_len;
	struct	sockaddr_in server;

	char msg[MAX_SIZE];
	char * hdBuffer = (char*)malloc(sizeof(char)* HEADER_SIZE);
	memset(hdBuffer, 0, HEADER_SIZE);

	LPWSABUF wsaBuffer = (LPWSABUF)malloc(sizeof(WSABUF));
	wsaBuffer->len = HEADER_SIZE;
	wsaBuffer->buf = hdBuffer;

	if (st->protocol == TCP){
		if ((status = WSARecv(recv, wsaBuffer, 1, &RecvBytes, &Flags, NULL, NULL)) == SOCKET_ERROR){
			sprintf_s(msg, "Error %d in TCP WSARecv(header) with return of %d\n", WSAGetLastError(), status);
			activity(msg, EB_STATUSBOX);
		}

		if (wsaBuffer->buf[0] != ';'){ // I really should have used an uncommon character here
			return -1;
		}
	}
	else{
		server_len = sizeof(server);
		if ((status = WSARecvFrom(st->server_socket, wsaBuffer, 1, &RecvBytes, &Flags, (struct sockaddr *)&server, &server_len, NULL, NULL)) == SOCKET_ERROR){
			return -1;
		}
		acknowledge(hwnd);
	}

	grab_header_info(hdBuffer);
	return 1;
}