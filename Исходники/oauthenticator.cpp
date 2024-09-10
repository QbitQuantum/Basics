void OAuthenticator::StartAuthorisation(const QString& oauth_endpoint,
                                        const QString& token_endpoint,
                                        const QString& scope) {
  token_endpoint_ = QUrl(token_endpoint);
  LocalRedirectServer* server = new LocalRedirectServer(this);
  server->Listen();

  QUrl url = QUrl(oauth_endpoint);
  url.addQueryItem("response_type", "code");
  url.addQueryItem("client_id", client_id_);
  QUrl redirect_url;

  const QString port = QString::number(server->url().port());

  if (redirect_style_ == RedirectStyle::REMOTE) {
    redirect_url = QUrl(kRemoteURL);
    redirect_url.addQueryItem("port", port);
  } else if (redirect_style_ == RedirectStyle::REMOTE_WITH_STATE) {
    redirect_url = QUrl(kRemoteURL);
    url.addQueryItem("state", port);
  } else {
    redirect_url = server->url();
  }

  url.addQueryItem("redirect_uri", redirect_url.toString());
  url.addQueryItem("scope", scope);

  NewClosure(server, SIGNAL(Finished()), this, &OAuthenticator::RedirectArrived,
             server, redirect_url);

  QDesktopServices::openUrl(url);
}