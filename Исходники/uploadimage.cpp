bool uploadImage::uploadFile(std::string filepath,std::string label, int Authencity){

    QEventLoop eventLoop;
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    QHttpPart textPart2, textPart3,textPart4,textPart5;
    textPart2.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"attendantID\""));
    QString Label=QString::fromStdString(label);
    textPart2.setBody(Label.toLatin1());


    textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"submit\""));
    textPart.setBody("Upload image");

    textPart3.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"Authencity\""));
    textPart3.setBody(QByteArray::number(Authencity));

    textPart4.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"systemCode\""));
    textPart4.setBody(networkManagement::systemCode.toUtf8());
    //
     time_t now = time(0);
     tm *ltm = localtime(&now);

       // print various components of tm structure.
       QString dateTime;
       dateTime=QString::number(1900 + ltm->tm_year) + "-" +QString::number(1 + ltm->tm_mon)+
               "-"+QString::number(ltm->tm_mday)+" "+
               QString::number(ltm->tm_hour)+":"+QString::number(ltm->tm_min)
               +":"+QString::number(ltm->tm_sec);

    textPart5.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"currentTime\""));
    //QString just="12-03-2015 00:01:29";

    textPart5.setBody(dateTime.toUtf8());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"fileToUpload\" ; filename=\""
                                 +QString::fromStdString(filepath)+"\""));
    QFile *file = new QFile(QString::fromStdString(filepath));
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    multiPart->append(textPart);
    multiPart->append(textPart2);
    multiPart->append(textPart3);
    multiPart->append(imagePart);
    multiPart->append(textPart4);
    multiPart->append(textPart5);

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString(MainWindow::serverAddress+"/uploader.php") ) );
    QNetworkReply *reply = mgr.post(req,multiPart);


    multiPart->setParent(reply);
      eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString strx=reply->readAll();
        qDebug()<<strx;

         //   qDebug()<<propertyKeys;
        delete reply;
        return true;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return false;
    }

}