void WebClient::postLogon(const ParamsT& params)
{
    QNetworkRequest request;
    request.setUrl(url_.toString() + params["service"] );
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray content = createContentBase64(params);
    qDebug() << "POST Sending: " << content;

    reply_.reset( netmgr_.post(request, content) );
    connect(reply_.data(), SIGNAL(finished()),
            this, SLOT(finished()));
    connect(reply_.data(), SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(reply_.data(), SIGNAL(error(NetworkError)),
            this, SLOT(connectionError(NetworkError)));

    QMutexLocker guard(&threadSafe_);
    handler_->onStateChanged(state_ = InProgress);
}