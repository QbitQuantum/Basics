/*****************************************************************************
  Function:
	int send( SOCKET s, const char* buf, int len, int flags )
	
  Summary:
	The send function is used to send outgoing data on an already
	connected socket.

  Description:
	The send function is used to send outgoing data on an already
	connected socket. This function is used to send a reliable,
	ordered stream of data bytes on a socket of type SOCK_STREAM
	but can also be used to send datagrams on a socket of type SOCK_DGRAM.

  Precondition:
	connect function should be called for TCP and UDP sockets.
	Server side, accept function should be called.

  Parameters:
	s - Socket descriptor returned from a previous call to socket.
	buf - application data buffer containing data to transmit.
	len - length of data in bytes.
	flags - message flags. Currently this field is not supported.

  Returns:
	On success, send returns number of bytes sent. In case of
	error, returns SOCKET_ERROR. a zero indicates no data send.

  Remarks:
	None.
  ***************************************************************************/
int send( SOCKET s, const char* buf, int len, int flags )
{
	return sendto(s, buf, len, flags, NULL, 0);
}