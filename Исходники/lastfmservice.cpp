void LastFMService::Authenticate() {
  QUrl url("https://www.last.fm/api/auth/");
  url.addQueryItem("api_key", kApiKey);

  LocalRedirectServer* server = new LocalRedirectServer(this);
  server->Listen();

  url.addQueryItem("cb", server->url().toString());

  NewClosure(server, SIGNAL(Finished()), [this, server]() {
    server->deleteLater();

    const QUrl& url = server->request_url();
    QString token = url.queryItemValue("token");

    QUrl session_url("https://ws.audioscrobbler.com/2.0/");
    session_url.addQueryItem("api_key", kApiKey);
    session_url.addQueryItem("method", "auth.getSession");
    session_url.addQueryItem("token", token);
    session_url.addQueryItem("api_sig", SignApiRequest(session_url.queryItems()));

    QNetworkReply* reply = network_->get(QNetworkRequest(session_url));
    NewClosure(reply, SIGNAL(finished()), this, SLOT(AuthenticateReplyFinished(QNetworkReply*)), reply);
  });