bool
SocketRegistry<T>::reconnect(const char * host) {
    for(Uint32 i=0; i < m_nSocketClients; i++) {
        SocketClient * socketClient = m_socketClients[i];
        if(strcmp(socketClient->gethostname(), host)==0) {
            if(!socketClient->isConnected()) {
                if(socketClient->openSocket() > 0)
                    return true;
                else return false;
            }
        }
    }
    return false;
}