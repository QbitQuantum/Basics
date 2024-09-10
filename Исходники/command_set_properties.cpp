void CommandSetFileProperties::reexecuteQuery()
{
    Q_D(CommandSetFileProperties);


    QString urlStr("https://www.googleapis.com/drive/v2/files");

    if (!d->fileInfo.id().isEmpty())
        urlStr += QString("/%1/properties").arg(d->fileInfo.id());
    QUrl url(urlStr);
    QNetworkRequest request(url);
    setRequestAccessToken(request, session()->accessToken());

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");

    Q_FOREACH (const QString& key,d->fields.keys()) {
        currentKey=key;
        QVariantMap fileInfoMap;
        fileInfoMap.insert(KEY_STRING,key);
        fileInfoMap.insert(VALUE_STRING,d->fields[key]);
        fileInfoMap.insert(VISIBILITY_STRING,"PUBLIC");
        QByteArray body = QJson::Serializer().serialize(fileInfoMap);

        QNetworkReply* reply = session()->networkManager()->post(request, body);


        connect(reply, SIGNAL(finished()), this, SLOT(queryFinished()));


        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),SLOT(queryFailed(QNetworkReply::NetworkError)));

        reply->setParent(this);
    }




}