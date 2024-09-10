void Syncer::send(QMap<QString, QString>& posts, QStringList& files)
{
    QNetworkRequest request(QUrl(url + posts["command"]));
    QHttpMultiPart* parts = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMapIterator<QString, QString> i(posts);
    while (i.hasNext()) {
        i.next();
        QHttpPart* part = new QHttpPart();
        part->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\""+ i.key() +"\""));
        part->setBody(i.value().toUtf8());
        parts->append(*part);
    }

    foreach (QString filename, files) {
        QFileInfo finfo(filename);
        QFile* file = new QFile(finfo.absoluteFilePath());
        if (file->open(QIODevice::ReadOnly)) {
            QHttpPart* part = new QHttpPart();
            part->setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/"+ finfo.suffix().toLower() +""));
            part->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; filename=\""+ finfo.fileName() +"\""));
            part->setBodyDevice(file);
            file->setParent(parts); // for delete time
            parts->append(*part);
        }
    }