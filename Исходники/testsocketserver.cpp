void multicastServer()
{
    char buffer[6];
    DgramSocket sock;
    Address client;

    cout << "Dgram multicast server: Start" << endl;
    sock.open();
    sock.setReusePort(true);
    sock.bind(AnyAddress(23344));
    sock.join(Address("224.0.0.50"));
    sock.join(Address("224.0.0.52"));
    sock.join(Address("224.0.0.53"));
    sock.leave(Address("224.0.0.52"));
    do
    {
        sock.recvFrom(buffer,6,client);
        sock.sendTo(buffer,6,client);
        cout << client.getHost() << " " << buffer << endl;
    } while(strcmp(buffer,"_END_"));
    sock.close();
    cout << "Dgram multicast server: OK" << endl;
}