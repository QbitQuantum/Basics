void Sender::onReadyRead() {
    // Check whether error occurs
    if (getChar(socket) != 0) {
        closeAll();
        emit error();
        return;
    }

    QByteArray buf;
    switch (step) {
    case SEND_SIZE:
        file = new QFile(filepath);
        if (!file->open(QFile::ReadOnly)) {
            closeAll();
            emit error();
            return;
        }
        socket->write(QByteArray::number(file->size()));
        socket->flush();
        step = SEND_DATA;
        break;

    case SEND_DATA:
        buf = file->read(4096);
        if (!buf.isEmpty()) {
            socket->write(buf);
            socket->flush();
        }
        else { // finish
            closeAll();
            emit finished();
        }
        break;
    default:break;
    }
}