// Constructs a new QIODevice (in this case a QUdpSocket) and returns it
// after binding the socket to the port specified in the XML node and read by
// the constructor of the abstract chunker.
QIODevice* K7Chunker::newDevice()
{
    QUdpSocket* udpSocket = new QUdpSocket;

    if (!udpSocket->bind(port(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint ))
    {
        std::cerr << "K7Chunker::newDevice(): Unable to bind to UDP port!" << udpSocket->errorString().toStdString() << std::endl;
    }

    return udpSocket;
}