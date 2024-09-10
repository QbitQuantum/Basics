void Toasty::slotNotify(Snore::Notification notification)
{
    QString key = settingsValue(ToastyConstants::DeviceID).toString();
    if (key.isEmpty()) {
        return;
    }
    QNetworkRequest request(QUrl::fromUserInput(QLatin1String("http://api.supertoasty.com/notify/") + key));
    QHttpMultiPart *mp = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart title;
    title.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QLatin1String("form-data; name=\"title\"")));
    title.setBody(notification.title().toUtf8().constData());
    mp->append(title);

    QHttpPart text;
    text.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QLatin1String("form-data; name=\"text\"")));
    text.setBody(notification.text().toUtf8().constData());
    mp->append(text);

    QHttpPart app;
    app.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QLatin1String("form-data; name=\"sender\"")));
    app.setBody(notification.application().name().toUtf8().constData());
    mp->append(app);

    QHttpPart icon;

    icon.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QLatin1String("form-data; name=\"image\"; filename=\"") + notification.icon().localUrl(QSize(128, 128)) + QLatin1Char('"')));
    icon.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(QLatin1String("image/png")));
    QFile *file = new QFile(notification.icon().localUrl(QSize(128, 128)));
    file->open(QIODevice::ReadOnly);
    icon.setBodyDevice(file);
    mp->append(icon);

    QNetworkReply *reply =  m_manager.post(request, mp);
    mp->setParent(reply);
    file->setParent(reply);

    connect(reply, &QNetworkReply::finished, [reply]() {
        qCDebug(SNORE) << reply->error();
        qCDebug(SNORE) << reply->readAll();
        reply->close();
        reply->deleteLater();
    });

}