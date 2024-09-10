LinSocket::LinSocket(short port, const char *protocol)
{
  struct protoent *pe;
  std::string s((char *)protocol);

  if ((pe = getprotobyname(protocol)) == NULL)
	return;
  if (s.compare("TCP") == 0)
  {
    this->_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  }
  else
  {
    this->_fd = socket(PF_INET, SOCK_DGRAM, pe->p_proto);
  };
  this->_port = port;
  if (this->_fd == -1)
	throw "socket failed";
}