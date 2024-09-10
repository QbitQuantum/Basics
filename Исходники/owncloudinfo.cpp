QNetworkReply* ownCloudInfo::getDirectoryListing( const QString& dir )
{
    QNetworkRequest req;
    req.setUrl( QUrl( webdavUrl(_connection) + dir ) );
    req.setRawHeader("Depth", "1");
    QByteArray xml("<?xml version=\"1.0\" ?>\n"
                   "<d:propfind xmlns:d=\"DAV:\">\n"
                   "  <d:prop>\n"
                   "    <d:resourcetype/>\n"
                   "  </d:prop>\n"
                   "</d:propfind>\n");
    QBuffer *buf = new QBuffer;
    buf->setData(xml);
    buf->open(QIODevice::ReadOnly);
    QNetworkReply *reply = davRequest("PROPFIND", req, buf);
    buf->setParent(reply);

    if( reply->error() != QNetworkReply::NoError ) {
        qDebug() << "getting quota: request network error: " << reply->errorString();
    }

    connect( reply, SIGNAL( finished()), SLOT(slotGetDirectoryListingFinished()) );
    connect( reply, SIGNAL( error(QNetworkReply::NetworkError)),
             this, SLOT( slotError(QNetworkReply::NetworkError)));
    return reply;
}