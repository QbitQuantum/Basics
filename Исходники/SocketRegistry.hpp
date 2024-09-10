inline
bool 
SocketRegistry<T>::performSend(const char * buf, Uint32 len, const char * remotehost)
{
  SocketClient * socketClient;
  for(Uint32 i=0; i < m_nSocketClients; i++) {
    socketClient = m_socketClients[i];
    if(strcmp(socketClient->gethostname(), remotehost)==0) {
      if(socketClient->isConnected()) {
	if(socketClient->writeSocket(buf, len)>0)
	  return true;
	else
	  return false;
      }
    }
  }
  return false;
}