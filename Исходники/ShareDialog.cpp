// Documentation is at:
// https://strava.pbworks.com/w/page/39241255/v2%20upload%20create
void
StravaUploader::requestUploadStrava()
{
    parent->progressLabel->setText(tr("Upload ride to Strava..."));
    parent->progressBar->setValue(parent->progressBar->value()+10/parent->shareSiteCount);

    QEventLoop eventLoop;
    QNetworkAccessManager networkMgr;

    int year = ride->fileName.left(4).toInt();
    int month = ride->fileName.mid(5,2).toInt();
    int day = ride->fileName.mid(8,2).toInt();
    int hour = ride->fileName.mid(11,2).toInt();
    int minute = ride->fileName.mid(14,2).toInt();;
    int second = ride->fileName.mid(17,2).toInt();;

    QDate rideDate = QDate(year, month, day);
    QTime rideTime = QTime(hour, minute, second);
    QDateTime rideDateTime = QDateTime(rideDate, rideTime);

    connect(&networkMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestUploadStravaFinished(QNetworkReply*)));
    connect(&networkMgr, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

    TcxFileReader reader;

    QUrl url = QUrl( "https://www.strava.com/api/v3/uploads" ); // The V3 API doc said "https://api.strava.com" but it is not working yet
    QNetworkRequest request = QNetworkRequest(url);

    //QString boundary = QString::number(qrand() * (90000000000) / (RAND_MAX + 1) + 10000000000, 16);
    QString boundary = QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();

    QByteArray file = reader.toByteArray(context, ride->ride(), parent->altitudeChk->isChecked(), parent->powerChk->isChecked(), parent->heartrateChk->isChecked(), parent->cadenceChk->isChecked());

    // MULTIPART *****************

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->setBoundary(boundary.toLatin1());

    QHttpPart accessTokenPart;
    accessTokenPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"access_token\""));
    accessTokenPart.setBody(token.toLatin1());

    QHttpPart activityTypePart;
    activityTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"activity_type\""));
    activityTypePart.setBody("ride");

    QHttpPart activityNamePart;
    activityNamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"activity_name\""));
    activityNamePart.setBody(QString(parent->titleEdit->text()).toLatin1());

    QHttpPart dataTypePart;
    dataTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"data_type\""));
    dataTypePart.setBody("tcx");

    QHttpPart externalIdPart;
    externalIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"external_id\""));
    externalIdPart.setBody("Ride");

    QHttpPart privatePart;
    privatePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"private\""));
    privatePart.setBody("TRUE");

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/xml"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"file.tcx\"; type=\"text/xml\""));
    filePart.setBody(file);


    multiPart->append(accessTokenPart);
    multiPart->append(activityTypePart);
    multiPart->append(activityNamePart);
    multiPart->append(dataTypePart);
    multiPart->append(externalIdPart);
    multiPart->append(privatePart);
    multiPart->append(filePart);

    QScopedPointer<QNetworkReply> reply( networkMgr.post(request, multiPart) );
    multiPart->setParent(reply.data());

    parent->progressBar->setValue(parent->progressBar->value()+30/parent->shareSiteCount);
    parent->progressLabel->setText(tr("Upload ride... Sending to Strava"));

    eventLoop.exec();
}