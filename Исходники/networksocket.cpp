void NetworkSocket::showInfo() const {

    qDebug() << "-------------------[ SOCKET ]---------------------";
    qDebug() << " Protocol type . . : " << getProtocolType();
    qDebug() << " ReceiveQ. . . . . : " << getReceiveQ()<< " bytes";
    qDebug() << " SendQ . . . . . . : " << getSendQ() << " bytes";
    qDebug() << " Local Address . . : " << getLocalAddress() << " bytes";
    qDebug() << " Foreign Address . : " << getForeignAddress();
    qDebug() << " State . . . . . . : " << getState();
    qDebug() << " PID . . . . . . . : " << getPID();
    qDebug() << " Program Name. . . : " << getProgramName();
    qDebug() << "--------------------------------------------------";
}