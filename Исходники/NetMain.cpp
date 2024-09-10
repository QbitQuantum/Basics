// ---------------------------------------------
void testSocket(string ip, unsigned short port) {
    Socket* socket = new Socket("null", 0);

    Socket::InetAddressPort remoteAddrAndPort;
    remoteAddrAndPort.port = port;
    Socket::getSockaddrByIpAndPort(&remoteAddrAndPort.addr, ip, port);

    socket->makeNonBlocking();
    while (true) {
        bool result  = socket->connect(remoteAddrAndPort);
        if (result) {
            cout << "connect success!" << endl;

            cm::Thread::sleep(100);

            char sendData[] = "TCP client request";
            int numberOfBytesSent;
            if (SKT_SUCC == socket->send(sendData, strlen(sendData), numberOfBytesSent)) {
                assert(numberOfBytesSent == strlen(sendData));
                cout << "send " << numberOfBytesSent << " bytes data complete" << endl;

                DataBuffer* response = new DataBuffer();
                int numOfBytesRecved = 0;

                while (true) {
                    result = socket->recv(response->getEndOfDataPointer(), response->getSize() - response->getLength(), numOfBytesRecved);
                    assert(result != SKT_ERR);
                    if (result == SKT_SUCC) {
                        assert(numOfBytesRecved != 0);
                        response->increaseDataLength(numOfBytesRecved);
                        cout << "recv " << numOfBytesRecved << " bytes data: " << response->getData() << endl;
                        response->reset();
                        break;
                    } else {
                        cm::Thread::sleep(1);
                    }
                }
            }

            socket->close();
            break;
        } else {
            cm::Thread::sleep(1);
        } 
    }
}