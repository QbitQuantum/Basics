SOCKETALT NetClient::init( const char *addr, unsigned short port, std::string &error )
{
    if ( clt_tcp_sock && clt_tcp_sock->valid() ) clt_tcp_sock->disconnect( "NC_init_tcp" );
    if ( clt_udp_sock && clt_udp_sock->valid() ) NetUIUDP::disconnectSaveUDP( *clt_udp_sock );
    lastsave.clear();
    netversion = 0;
    if (addr == NULL) {
        addr = _serverip.c_str();
        port = _serverport;
    }
    COUT<<" enter "<<__PRETTY_FUNCTION__
        <<" with "<<addr<<":"<<port<<endl;

    _sock_set.start();

    string strnetatom;
    strnetatom = vs_config->getVariable( "network", "network_atom", "" );
    if (strnetatom == "")
        NETWORK_ATOM = 0.2;
    else
        NETWORK_ATOM = (double) atof( strnetatom.c_str() );
    *this->clt_tcp_sock = NetUITCP::createSocket( addr, port, _sock_set );
    this->lossy_socket  = this->clt_tcp_sock;
    if ( !clt_tcp_sock->valid() )
        return *this->clt_tcp_sock;
    COUT<<"created TCP socket ("<<addr<<","<<port<<") -> "<<this->clt_tcp_sock<<endl;

    /*
     *  if( this->authenticate() == -1)
     *  {
     *       perror( "Error login in ");
     *       return -1;
     *  }
     */
    Packet join;
    join.send( CMD_CONNECT, CLIENT_NETVERSION, "", 0, SENDRELIABLE, NULL,
              *this->clt_tcp_sock, __FILE__, PSEUDO__LINE__( 407 ) );
    this->enabled = 1;

    string  login_tostr = vs_config->getVariable( "network", "connecttimeout", "10" );
    timeval tv = {atoi( login_tostr.c_str() ), 0};
    int     timeout     = 0;
    Packet  packet;
    while (!timeout) {
        int recvd = this->recvMsg( &packet, &tv );
        if (recvd == 0) {
            error   = "Connection to game server timed out!";
            timeout = 1;
        } else if (recvd < 0) {
            char str[127];
            sprintf( str, "NETWORK ERROR in recieving socket (error number %d)!!!",
#ifdef _WIN32
                     WSAGetLastError()
#else
                     errno
#endif
                   );
            error   = str;
            timeout = 1;
        } else if (this->netversion) {
            break;
        }
    }
    if (!this->netversion) {
        if ( error.empty() )
            error = "Unable to receive a valid version from this server.";
        timeout = 1;
    }
    if (timeout)
        clt_tcp_sock->disconnect( "NCinit_timedout" );
    return *this->clt_tcp_sock;
}