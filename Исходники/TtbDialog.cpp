void
TtbDialog::requestUpload()
{
    assert(sessionId.length() > 0 );

    progressLabel->setText(tr("preparing upload ..."));

    QHttpMultiPart *body = new QHttpMultiPart( QHttpMultiPart::FormDataType );

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
    QVariant("form-data; name=\"upload_submit\""));
    textPart.setBody("hrm");
    body->append( textPart );


    QString fname = context->athlete->home.absoluteFilePath(".ttbupload.pwx" );
    QFile *uploadFile = new QFile( fname );
    uploadFile->setParent(body);

    PwxFileReader reader;
    reader.writeRideFile(context, ride->ride(), *uploadFile );
    progressBar->setValue(12);

    int limit = proMember
        ? 8 * 1024 * 1024
        : 4 * 1024 * 1024;
    if( uploadFile->size() >= limit ){
        progressLabel->setText(tr("temporary file too large for upload: %1 > %1 bytes")
            .arg(uploadFile->size())
            .arg(limit) );
        closeButton->setText(tr("&Close"));
        return;
    }

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
    QVariant("application/occtet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
    QVariant("form-data; name=\"file\"; filename=\"gc-upload-ttb.pwx\""));
    uploadFile->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(uploadFile);
    body->append( filePart );


    progressLabel->setText(tr("uploading ..."));

    currentRequest = reqUpload;

    QUrl url( TTB_URL + "/file/upload" );
    url.addQueryItem( "view", "xml" );
    url.addQueryItem( "sso", sessionId );

    QNetworkRequest request = QNetworkRequest(url);
    request.setRawHeader( "Accept-Encoding", "identity" );
    request.setRawHeader( "Accept", "application/xml" );
    request.setRawHeader( "Accept-Charset", "utf-8" );

    QNetworkReply *reply = networkMgr.post( request, body );
    body->setParent( reply );

    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this,
        SLOT(uploadProgress(qint64,qint64)));
}