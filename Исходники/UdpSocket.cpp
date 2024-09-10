bool			Network::UDPSocketWindows::sendPacket(Packet const &p, struct sockaddr const *sockAddr) const
{
  DWORD			flags = 0;
  DWORD			bytesSent = 0;
  WSABUF		buf;

  buf.len = p.getSize();
  buf.buf = const_cast<char*>(reinterpret_cast<char const *>(&p.getContent()));

	if (WSASendTo(this->fd_,&buf, 1, &bytesSent, 0, sockAddr, sizeof(*sockAddr), 0, 0) == -1)
    return (false);
  return (true);
}