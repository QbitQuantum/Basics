 ///Shutdown the socket.
 UDPSocket::~UDPSocket( void )
 {
   shutdown(socket, SD_BOTH);
 }