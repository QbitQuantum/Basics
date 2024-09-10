void BoxitSocket::sendData(quint16 msgID, QByteArray data) {
    // Send data in multiple data packages, if data is too big...
    while (true) {
        QByteArray subData = data.mid(0, BOXIT_SOCKET_MAX_SIZE);
        data.remove(0, BOXIT_SOCKET_MAX_SIZE);

        quint16 subMsgID = msgID;
        if (!data.isEmpty())
            subMsgID = MSG_DATA_PACKAGE_MULTIPLE;

        // Send data
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out << (quint16)0;
        out << (quint16)subMsgID;
        out << subData;
        out.device()->seek(0);
        out << (quint16)(block.size() - 2*sizeof(quint16));

        write(block);
        flush();

        waitForBytesWritten(2000);

        if (data.isEmpty())
            break;
    }
}