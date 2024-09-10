bool FstReader::addPart(const QString &path, const QString& name) {
    QFile* file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "[ERROR] Couldn't open " << file->fileName();
        return false;
    }
    
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data;"
                   " name=\"" + name.toUtf8() +  "\";"
                   " filename=\"" + QFileInfo(*file).fileName().toUtf8() +  "\"");
    part.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    part.setBodyDevice(file);
    _dataMultiPart->append(part);
    file->setParent(_dataMultiPart);
    
    return true;
}