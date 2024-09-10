QNetworkReply *	NetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData)
{
    QByteArray data;
    QBuffer* buffer = 0;

    // cache the content first
    if (outgoingData) {
        buffer = new QBuffer(this);
        data = outgoingData->readAll();
        buffer->setData(data);
    }

    if (d->ShouldLogRequestResponse) {
        qDebug() << "Queueing Request: " << req.url().toString();
    }

    QNetworkReply* reply = QNetworkAccessManager::createRequest(op, req, buffer);
    reply->ignoreSslErrors();

    if (outgoingData) {
        qDebug() << "Request Details# op=" << op << ", url=" <<  req.url().toString() << ", data("<<data.length() <<")=" << data;
        if (d->removeRequestInfo(reply)) {
            qWarning() << "Same request aleady cached. So going to remove reference to old one.";
        }
        d->DataMap.insert(reply, new RequestInfo(op, data, buffer));
    }

    return reply;
}