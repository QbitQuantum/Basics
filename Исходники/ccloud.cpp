bool ccloud::syncMobile(QDate date)
{
    qDebug() << "mobile sync kutsu";
    QString syncFileName = QDir::tempPath() + "/theocbase_transfer_" + QDate::currentDate().toString(Qt::ISODate) + ".thb";
    QDate tempdate = date.addDays(4 * -7);

    csync syn;
    syn.CreateXMLFile(syncFileName, tempdate,true, false, true, true, false, true,false,8);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"import\""));
    textPart.setBody("import");

    int userid = this->userId();
    QHttpPart useridPart;
    useridPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_id\""));
    useridPart.setBody( QVariant(userid).toString().toLatin1() );

    QHttpPart fromPart;
    fromPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"from\""));
    fromPart.setBody("fromTheocBase");

    QHttpPart datePart;
    datePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"date\""));
    datePart.setBody(QDate::currentDate().toString("yyyy.MM.dd").toLatin1() + "-" +
                QTime::currentTime().toString("HHmmss").toLatin1());

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/xml"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\""));
    QFile *file = new QFile(syncFileName);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(textPart);
    multiPart->append(useridPart);
    multiPart->append(datePart);
    multiPart->append(filePart);
    multiPart->append(fromPart);
    QUrl url("https://api.theocbase.net/theocbase_get.php");
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request,multiPart);
    multiPart->setParent(reply);

    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QString replystr = reply->readAll();
        qDebug() << "sync mobile" << replystr;

        return true;
    } else {
        QMessageBox::information(0,"","Error when synchronizing mobile data\n" + reply->errorString());
        return false;
    }

}