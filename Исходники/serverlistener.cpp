bool ServerListener::postTaskResults(QString taskId, QString filepath)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"task_assignment_id\""));
    textPart.setBody(taskId.toUtf8());

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("attachment; name=\"result_file\"; filename=\"out.csv\""));
    QFile *file = new QFile(filepath);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(textPart);
    multiPart->append(filePart);

    QEventLoop loop;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request = QNetworkRequest(QUrl(ClientSettingsManager::getServerUrl() + "postTaskData"));
    connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    manager->post(request, multiPart);
    loop.exec();
    file->close();
    delete multiPart;
    delete manager;
    return true;
}