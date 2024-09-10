/**
 * @details
 * Constructs a new QIODevice (in this case a QUdpSocket) and returns it
 * after binding the socket to the port specified in the XML node and read by
 * the constructor of the abstract chunker.
 */
QIODevice* LofarDataSplittingChunker::newDevice()
{
    QUdpSocket* socket = new QUdpSocket;

    if (!socket->bind(port(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint ))
        cerr << "LofarDataSplittingChunker::newDevice(): "
        "Unable to bind to UDP port!" <<
        socket->errorString().toStdString() << std::endl;

    return socket;
}