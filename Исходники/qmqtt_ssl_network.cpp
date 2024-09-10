void QMQTT::SslNetwork::onSocketReadReady()
{
    QIODevice *ioDevice = _socket->ioDevice();
    while(!ioDevice->atEnd())
    {
        if(_bytesRemaining == 0)
        {
            if (!ioDevice->getChar(reinterpret_cast<char *>(&_header)))
            {
                // malformed packet
                emit error(QAbstractSocket::OperationError);
                ioDevice->close();
                return;
            }

            _bytesRemaining = readRemainingLength();
            if (_bytesRemaining < 0)
            {
                // malformed remaining length
                emit error(QAbstractSocket::OperationError);
                ioDevice->close();
                return;
            }
        }

        QByteArray data = ioDevice->read(_bytesRemaining);
        _buffer.append(data);
        _bytesRemaining -= data.size();

        if(_bytesRemaining == 0)
        {
            Frame frame(_header, _buffer);
            _buffer.clear();
            emit received(frame);
        }
    }
}