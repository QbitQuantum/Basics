void imgUploader::uploadImage(QString FileName, QString PhpUploadURL, QString FieldName)
{

    QUrl serviceUrl = QUrl(PhpUploadURL);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QNetworkRequest request(serviceUrl);
    request.setRawHeader("User-Agent", UserAgent.toAscii());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + FieldName + "\"; filename=\"" + FileName +  "\""));

    QFile *file = new QFile(FileName);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    file->open(QIODevice::ReadOnly);

    imagePart.setBodyDevice(file);
    multiPart->append(imagePart);

    // Call the webservice
    //QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    currentUpload =  manager.post(request, multiPart);

    connect(currentUpload,SIGNAL(uploadProgress(qint64,qint64)),this, SLOT(onUploadProgress(qint64,qint64)));
    connect(currentUpload, SIGNAL(finished()),this,SLOT(onUploadFinished()));

    Uploading = true;
    //reply->deleteLater();
}