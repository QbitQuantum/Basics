void DropboxAuthenticator::Authorise() {
  LocalRedirectServer* server = new LocalRedirectServer(this);
  server->Listen();

  NewClosure(server, SIGNAL(Finished()), this,
             SLOT(RedirectArrived(LocalRedirectServer*)), server);

  QUrl url(kAuthoriseEndpoint);
  url.addQueryItem("oauth_token", token_);
  url.addQueryItem("oauth_callback", server->url().toString());

  QDesktopServices::openUrl(url);
}