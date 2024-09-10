nsUDPSocket::~nsUDPSocket()
{
  CloseSocket();
  MOZ_COUNT_DTOR(nsUDPSocket);
}