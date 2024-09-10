void BrisaControlPoint::replyFinished(QNetworkReply *reply) {
    QTemporaryFile *rootXml = new QTemporaryFile();
    if (!rootXml->open()) {
        qWarning() << "Brisa Control Point: Failed to open file for writing root XML.";
    } else {
        rootXml->write(reply->readAll());
        rootXml->seek(0);
        QUrl *urlBase = new QUrl(reply->url());

        BrisaControlPointDevice *device = new BrisaControlPointDevice(rootXml, urlBase);

        /* Fix embedded devices host/port attributes */
        QList<BrisaControlPointService*> serviceList = device->getServiceList();
        foreach(BrisaControlPointService *s, serviceList) {
                s->setAttribute(BrisaControlPointService::Host, urlBase->host());
                s->setAttribute(BrisaControlPointService::Port,
                        QString().setNum(urlBase->port()));
        }

        rootXml->remove();
        delete rootXml;
        delete urlBase;
        // deleteLater as per Qt documentation (see Detailed Description section of
        // QNetworkAccessManager class documentation for more details;
        reply->deleteLater();

        emit deviceFound(device);
    }