void
TrainingstagebuchUploader::requestUpload()
{
    assert(sessionId.length() > 0 );

    parent->progressLabel->setText(tr("preparing Trainingstagebuch.org data ..."));

    QHttpMultiPart *body = new QHttpMultiPart( QHttpMultiPart::FormDataType );

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
    QVariant("form-data; name=\"upload_submit\""));
    textPart.setBody("hrm");
    body->append( textPart );


    QString fname = context->athlete->home->temp().absoluteFilePath(".ttbupload.pwx" );
    QFile *uploadFile = new QFile( fname );
    uploadFile->setParent(body);

    PwxFileReader reader;
    reader.writeRideFile(context, ride->ride(), *uploadFile );
    parent->progressBar->setValue(parent->progressBar->value()+20/parent->shareSiteCount);

    int limit = proMember
        ? 8 * 1024 * 1024
        : 4 * 1024 * 1024;
    if( uploadFile->size() >= limit ){
        parent->errorLabel->setText(tr("temporary file too large for upload: %1 > %1 bytes")
            .arg(uploadFile->size())
            .arg(limit) );

        eventLoop.quit();
        return;
    }

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
    QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
    QVariant("form-data; name=\"file\"; filename=\"gc-upload-ttb.pwx\""));
    uploadFile->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(uploadFile);
    body->append( filePart );


    parent->progressLabel->setText(tr("sending to Trainingstagebuch.org ..."));

    currentRequest = reqUpload;

#if QT_VERSION > 0x050000
    QUrlQuery urlquery;
#else
    QUrl urlquery( TTB_URL + "/file/upload" );
#endif
    urlquery.addQueryItem( "view", "xml" );
    urlquery.addQueryItem( "sso", sessionId );


#if QT_VERSION > 0x050000
    QUrl url (TTB_URL + "/file/upload");
    url.setQuery(urlquery.query());
    QNetworkRequest request = QNetworkRequest(url);
#else
    QNetworkRequest request = QNetworkRequest(urlquery);
#endif

    request.setRawHeader( "Accept-Encoding", "identity" );
    request.setRawHeader( "Accept", "application/xml" );
    request.setRawHeader( "Accept-Charset", "utf-8" );

    QNetworkReply *reply = networkMgr.post( request, body );
    body->setParent( reply );
}