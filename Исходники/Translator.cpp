/*!
 * \brief Handle doc translation
 */
void Translator::fileTranslate(QString filePath)
{

    QDir outputDocDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    QString dirName = tr("Apertium Translated Documents");
    outputDocDir.mkdir(dirName);
    if (!outputDocDir.cd(dirName)) {
        emit fileTranslateRejected();
        return;
    }
    QFileInfo fileInfo(filePath);
#ifdef Q_OS_LINUX
    auto multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; filename=\"" + fileInfo.fileName() + "\"; name=\"file\""));
    auto file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        emit fileTranslateRejected();
        return;
    }
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QUrlQuery query;
    query.addQueryItem("langpair",
                       parent->getCurrentSourceLang() + "|" + parent->getCurrentTargetLang());
    QUrl url("http://localhost:2737/translateDoc?");
    QNetworkRequest request(QUrl(url.url() + query.query()));
    QNetworkAccessManager mngr;
    QEventLoop loop;
    QNetworkReply *reply = mngr.post(request, multiPart);
    connect(reply, &QNetworkReply::finished, [&]() {
        loop.exit();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            emit fileTranslateRejected();
            return;
        }
        QFile outDoc(outputDocDir.absoluteFilePath(fileInfo.baseName() + "_" +
                                                   parent->getCurrentSourceLang()
                                                   + "-" + parent->getCurrentTargetLang() + "." + fileInfo.completeSuffix()));
        if (!outDoc.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            emit fileTranslateRejected();
            reply->deleteLater();
            return;
        }
        outDoc.write(reply->readAll());
        outDoc.close();
        emit fileTranslated(outDoc.fileName());
        reply->deleteLater();
    });
    loop.exec();
#else
    if (fileInfo.suffix() == "txt")
        translateTxt(filePath, outputDocDir);
    else if (fileInfo.suffix() == "docx")
        translateDocx(filePath, outputDocDir);
    else if (fileInfo.suffix() == "pptx")
        translatePptx(filePath, outputDocDir);
    else if (fileInfo.suffix() == "xlsx")
        translateXlsx(filePath, outputDocDir);
    else if (fileInfo.suffix() == "html")
        translateHtml(filePath, outputDocDir);
    else if (fileInfo.suffix() == "rtf")
        translateRtf(filePath, outputDocDir);
#endif
}