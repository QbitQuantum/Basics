int TcpSocket::rawSendBytes(char *buffer, shared_int num_bytes)
{
  int rc = this->SOCKET_FAIL;

  rc = SEND(this->getSockHandle(), buffer, num_bytes, 0);
  
  return rc;
}