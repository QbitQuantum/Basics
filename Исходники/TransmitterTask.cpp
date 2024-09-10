/**
 * @brief TransmitterTask::run
 */
void TransmitterTask::run()
{
    QUdpSocket socket;
    socket.bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    socket.writeDatagram(data, address, port);
    socket.waitForBytesWritten();
    socket.close();
    qDebug() << "Task:" << address << ':' << port << "<-" << data;
}