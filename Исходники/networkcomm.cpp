void NetworkComm::addImage(QString key, const QByteArray value){
    QHttpPart* imagePart;
    imagePart = new QHttpPart();
    imagePart->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\""+key+"\"; filename=\"myfile.jpg\""));
    imagePart->setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QFile *file = new QFile(value);
    file->open(QIODevice::ReadOnly);
    imagePart->setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(*imagePart);
    //params.addQueryItem(key,value);
}