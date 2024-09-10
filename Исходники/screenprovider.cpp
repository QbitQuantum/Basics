void streamLoop(qintptr socketDesc, QQueue<QByteArray> &queue, bool& streaming) {

    QTcpSocket* socket = new QTcpSocket();
    // TCP_NODELAY + disable Nagle's algorithm
    socket->setSocketOption(QAbstractSocket::LowDelayOption, QVariant::fromValue(1));
    // Internetwork control
    socket->setSocketOption(QAbstractSocket::TypeOfServiceOption, QVariant::fromValue(192));
    socket->setSocketDescriptor(socketDesc);
    socket->readAll();

    QByteArray ContentType = ("HTTP/1.1 200 OK\r\n" \
                              "Server: test\r\n" \
                              "Cache-Control: no-cache\r\n" \
                              "Cache-Control: private\r\n" \
                              "Connection: close\r\n"\
                              "Pragma: no-cache\r\n"\
                              "Content-Type: multipart/x-mixed-replace; boundary=--boundary\r\n\r\n");

    socket->write(ContentType);

    while((socket->state() != QAbstractSocket::ClosingState ||
           socket->state() != QAbstractSocket::UnconnectedState) &&
           socket->state() == QAbstractSocket::ConnectedState &&
           streaming) {

        if(queue.empty()) { // no new frame available
            continue;
        }

        // make sure that the queue doesn't grow too big or
        // the OOM killer will kick in
        if(queue.length() > 20) {
            queue.clear();
            continue;
        }

        QByteArray boundary = ("--boundary\r\n" \
                               "Content-Type: image/jpeg\r\n" \
                               "Content-Length: ");

        QByteArray img  = queue.dequeue();
        boundary.append(QString::number(img.length()));
        boundary.append("\r\n\r\n");

        socket->write(boundary);
        socket->waitForBytesWritten();
        boundary.clear();
        socket->write(img);
        socket->waitForBytesWritten();
        img.clear();
    }

    socket->flush();
    socket->abort();
    socket->deleteLater();
    streaming = false;
    queue.clear();
    return;
}