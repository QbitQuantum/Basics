QNetworkReply* MNetworkManager::sendJWT(const QString url, QJsonObject &params, QString method ) {
    QJsonObject header;
    header["typ"] = "JWT";
    header["alg"] = "sha256";

    QByteArray encode;
    encode.append(QJsonDocument(header).toJson().toBase64(QByteArray::Base64Encoding));
    encode.append(".");
    encode.append(QJsonDocument(params).toJson().toBase64(QByteArray::Base64Encoding));
    QByteArray signature = QMessageAuthenticationCode::hash(encode, QByteArray(SECRET), QCryptographicHash::Sha256).toHex();

    QByteArray jwt;
    jwt.append(encode);
    jwt.append(".");
    jwt.append(signature);

    QString apiUrl = APIHOST;
    apiUrl.append(url);

    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setRawHeader("JWT", jwt);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QNetworkReply* reply;

    if (method == "post") {
        reply = this->post(request,multiPart);
    } else {
        reply = this->get(request);
    }
    multiPart->setParent(reply);

    return reply;
}