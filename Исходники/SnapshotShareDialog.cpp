void SnapshotShareDialog::uploadSnapshot() {

    if (AccountManager::getInstance().getAccountInfo().getDiscourseApiKey().isEmpty()) {
        QMessageBox::warning(this, "",
                             "Your Discourse API key is missing, you cannot share snapshots. Please try to relog.");
        return;
    }

    if (!_networkAccessManager) {
        _networkAccessManager = new QNetworkAccessManager(this);
    }

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart apiKeyPart;
    apiKeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_key\""));
    apiKeyPart.setBody(AccountManager::getInstance().getAccountInfo().getDiscourseApiKey().toLatin1());

    QFile* file = new QFile(_fileName);
    file->open(QIODevice::ReadOnly);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\"; filename=\"" + file->fileName() +"\""));
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(apiKeyPart);
    multiPart->append(imagePart);

    QUrl url(FORUM_UPLOADS_URL);
    QNetworkRequest request(url);

    QNetworkReply* reply = _networkAccessManager->post(request, multiPart);


    connect(reply, &QNetworkReply::finished, this, &SnapshotShareDialog::uploadRequestFinished);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
}