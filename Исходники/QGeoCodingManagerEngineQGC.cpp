QGeoCodeReply *QGeoCodingManagerEngineQGC::geocode(const QString &address, int limit, int offset, const QGeoShape &bounds)
{
    Q_UNUSED(limit);
    Q_UNUSED(offset);

    QNetworkRequest request;
    request.setRawHeader("User-Agent", m_userAgent);

    QUrl url(QStringLiteral("http://maps.googleapis.com/maps/api/geocode/json"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("sensor"), QStringLiteral("false"));
    query.addQueryItem(QStringLiteral("language"), locale().name().left(2));
    query.addQueryItem(QStringLiteral("address"), address);
    if (bounds.type() == QGeoShape::RectangleType) {
        query.addQueryItem(QStringLiteral("bounds"), boundingBoxToLtrb(bounds));
    }

    url.setQuery(query);
    request.setUrl(url);
    //qDebug() << url;

    QNetworkReply *reply = m_networkManager->get(request);
    reply->setParent(0);

    QGeoCodeReplyQGC *geocodeReply = new QGeoCodeReplyQGC(reply);

    connect(geocodeReply, SIGNAL(finished()), this, SLOT(replyFinished()));
    connect(geocodeReply, SIGNAL(error(QGeoCodeReply::Error,QString)),
            this, SLOT(replyError(QGeoCodeReply::Error,QString)));

    return geocodeReply;
}