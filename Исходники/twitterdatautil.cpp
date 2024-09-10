QByteArray TwitterDataUtil::authorizationHeader(const QByteArray &oauthConsumerKey,
                                                const QByteArray &oauthConsumerSecret,
                                                const QByteArray &requestMethod,
                                                const QByteArray &requestUrl,
                                                const std::vector<std::pair<QByteArray, QByteArray>> &parameters,
                                                const QByteArray &oauthToken,
                                                const QByteArray &oauthTokenSecret,
                                                const QByteArray &oauthNonce,
                                                const QByteArray &oauthTimestamp)
{
    // Twitter requires all requests to be signed with an authorization header.
    QByteArray nonce {oauthNonce};
    if (nonce.isEmpty()) {
        nonce = QUuid::createUuid().toByteArray().toBase64();
    }
    QByteArray timestamp {oauthTimestamp};
    if (timestamp.isEmpty()) {
        timestamp = QByteArray::number(qFloor(QDateTime::currentMSecsSinceEpoch() / 1000.0));
    }

    // now build up the encoded parameters map.  We use a map to perform alphabetical sorting.
    QMap<QByteArray, QByteArray> encodedParams {};
    encodedParams.insert(QByteArray("oauth_consumer_key").toPercentEncoding(), QByteArray(oauthConsumerKey).toPercentEncoding());
    encodedParams.insert(QByteArray("oauth_nonce").toPercentEncoding(), nonce.toPercentEncoding());
    encodedParams.insert(QByteArray("oauth_signature_method").toPercentEncoding(), QByteArray(OAUTH_SIGNATURE_METHOD).toPercentEncoding());
    encodedParams.insert(QByteArray("oauth_timestamp").toPercentEncoding(), timestamp.toPercentEncoding());
    encodedParams.insert(QByteArray("oauth_version").toPercentEncoding(), QByteArray(OAUTH_VERSION).toPercentEncoding());
    if (!oauthToken.isEmpty()) {
        encodedParams.insert(QByteArray("oauth_token").toPercentEncoding(), oauthToken.toPercentEncoding());
    }
    for (const std::pair<QByteArray, QByteArray> &parameter : parameters) {
        encodedParams.insert(parameter.first, parameter.second);
    }

    QByteArray parametersByteArray {};
    QList<QByteArray> keys = encodedParams.keys();
    for (const QByteArray &key : keys) {
        parametersByteArray += key + QByteArray("=") + encodedParams.value(key) + QByteArray("&");
    }
    parametersByteArray.chop(1);

    QByteArray signatureBaseString {requestMethod.toUpper() + QByteArray("&") + requestUrl.toPercentEncoding() + QByteArray("&") + parametersByteArray.toPercentEncoding()};
    QByteArray signingKey {oauthConsumerSecret.toPercentEncoding() + QByteArray("&") + oauthTokenSecret.toPercentEncoding()};

    QByteArray oauthSignature {QMessageAuthenticationCode::hash(signatureBaseString, signingKey, QCryptographicHash::Sha1).toBase64()};
    encodedParams.insert(QByteArray("oauth_signature").toPercentEncoding(), oauthSignature.toPercentEncoding());

    // now generate the Authorization header from the encoded parameters map.
    // we need to remove the query items from the encoded parameters map first.
    QByteArray authHeader = QByteArray("OAuth ");

    for (const std::pair<QByteArray, QByteArray> &parameter : parameters) {
        encodedParams.remove(parameter.first);
    }
    keys = encodedParams.keys();
    foreach (const QByteArray &key, keys) {
        authHeader += key + "=\"" + encodedParams.value(key) + "\", ";
    } 