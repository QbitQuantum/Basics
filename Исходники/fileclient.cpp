void do_ping(Socket::ptr sock, string ip, int port){
    debug("Pinging %s:%d\n", ip.c_str(), port);
    sock->connect(ip.c_str(), port);
    sock->send(PING + NEWLINE + NEWLINE);
    string response = sock->recv();
    if(response.substr(0, PONG.length()) != PONG){
        throw(gollum2411::socket_error("No PONG received"));
    }
}