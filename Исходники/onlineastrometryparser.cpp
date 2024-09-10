void OnlineAstrometryParser::uploadFile()
{
    QNetworkRequest request;

    QFile *fitsFile = new QFile(filename);
    bool rc = fitsFile->open(QIODevice::ReadOnly);
    if (rc == false)
    {
        align->appendLogText(i18n("Failed to open file %1. %2", filename, fitsFile->errorString()));
        delete (fitsFile);
        emit solverFailed();
        return;
    }

    QUrl url(Options::astrometryAPIURL());
    url.setPath("/api/upload");
    request.setUrl(url);

    QHttpMultiPart *reqEntity = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QVariantMap uploadReq;
    uploadReq.insert("publicly_visible", "n");
    uploadReq.insert("allow_modifications", "n");
    uploadReq.insert("session", sessionKey);
    uploadReq.insert("allow_commercial_use", "n");
    uploadReq.insert("scale_units", "arcminwidth");
    uploadReq.insert("scale_type", "ul");
    uploadReq.insert("scale_lower", lowerScale);
    uploadReq.insert("scale_upper", upperScale);
    uploadReq.insert("center_ra", center_ra);
    uploadReq.insert("center_dec", center_dec);
    uploadReq.insert("radius", radius);
    if (downsample_factor != 0)
        uploadReq.insert("downsample_factor", downsample_factor);
    if (parity != -1)
        uploadReq.insert("parity", parity);

    QJsonObject json = QJsonObject::fromVariantMap(uploadReq);
    QJsonDocument json_doc(json);

    QHttpPart jsonPart;

    jsonPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/text/plain");
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"request-json\"");
    jsonPart.setBody(json_doc.toJson(QJsonDocument::Compact));

    QHttpPart filePart;

    filePart.setHeader(QNetworkRequest::ContentTypeHeader,"application/octet-stream");
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"file\"; filename=\"%1\"").arg(filename));
    filePart.setBodyDevice(fitsFile);

    // Re-parent so that it get deleted later
    fitsFile->setParent(reqEntity);

    reqEntity->append(jsonPart);
    reqEntity->append(filePart);

    workflowStage = UPLOAD_STAGE;

    align->appendLogText(i18n("Uploading file..."));

    QNetworkReply *reply = networkManager->post(request, reqEntity);

    // The entity should be deleted when reply is finished
    reqEntity->setParent(reply);
}