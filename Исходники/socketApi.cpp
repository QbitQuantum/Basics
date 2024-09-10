DLLEXPORT double udp_send(double handle, const char *host, double port) {
    uint16_t intPort;
    try {
        intPort = numeric_cast<uint16_t> (port);
    } catch (bad_numeric_cast &e) {
        intPort = 0;
    }

    if (intPort == 0) {
        return false;
    }

    BufferPtr buffer = handles.find<Buffer> (handle);
    if(buffer) {
        if(!defaultUdpSocket) {
            defaultUdpSocket = UdpSocket::bind(0);
        }
        defaultUdpSocket->write(buffer->getData(), buffer->size());
        defaultUdpSocket->send(host, intPort);
        return true;
    }

    boost::shared_ptr<UdpSocket> sock = handles.find<UdpSocket>(handle);
    if(sock) {
        return sock->send(host, intPort);
    }
    return false;
}