//
// Socks5 Protocol implementation
//
void Server::open(Socket &s, Support &my)
{
    s.open(SOCK_STREAM);
    s.connect(my.mServer->address());
    secdebug("socks", "%d connected to server %s", s.fd(), string(my.mServer->address()).c_str());
    Byte request[] = { 5, 1, socksAuthPublic };
    s.write(request, sizeof(request));
    Byte reply[2];
    s.read(reply, sizeof(reply));
    if (reply[0] != 5 || reply[1] != socksAuthPublic) {
        secdebug("socks", "%d server failed (v%d auth=%d)", s.fd(), reply[0], reply[1]);
        s.close();
        UnixError::throwMe(EPROTONOSUPPORT);
    }
}