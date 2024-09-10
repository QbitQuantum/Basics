/// <summary>
/// Execute http post
/// </summary>
/// <param name="url">url for the http post</param>
/// <param name="data">string data to post</param>
/// <returns>Server answer</returns>
string VulkanDatabase::httpPost(string url, string data)
{
    manager = new QNetworkAccessManager(NULL);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart jsonPart;
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"data\"; filename=\"vulkanreport.json\""));
    jsonPart.setBody(QString::fromStdString(data).toLatin1());
    multiPart->append(jsonPart);

    QUrl qurl(QString::fromStdString(url));

    if (dbLogin)
    {
        qurl.setUserName(dbUser);
        qurl.setPassword(dbPass);
    }

    QNetworkRequest request(qurl);
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString replyStr(bytes);
        delete(manager);
        return replyStr.toStdString();
    }
    else
    {
        QString err;
        err = reply->errorString();
        delete(manager);
        return err.toStdString();
    }
}