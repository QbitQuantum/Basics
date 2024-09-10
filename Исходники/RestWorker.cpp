QByteArray
CRestWorker::send_request(const QNetworkRequest &req,
                          bool get,
                          int& http_status_code,
                          int& err_code,
                          int &network_error,
                          bool ignore_ssl_errors) {

  if (m_network_manager->networkAccessible() != QNetworkAccessManager::Accessible) {
    CApplicationLog::Instance()->LogError("Network isn't accessible : %d", (int)m_network_manager->networkAccessible());
    m_network_manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
  }

  err_code = RE_SUCCESS;
  network_error = 0;
  http_status_code = -1;

  QEventLoop loop;
  QTimer timer(&loop);
  timer.setSingleShot(true);
  timer.start(15000);

  QNetworkReply* reply =
      get ? m_network_manager->get(req) : m_network_manager->post(req, QByteArray());

  connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  if (!ignore_ssl_errors) {
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(ssl_errors_appeared(QList<QSslError>)));
  }
  else {
    QList<QSslError> errors2ignore;
    errors2ignore << QSslError(QSslError::CertificateUntrusted);
    errors2ignore << QSslError(QSslError::SelfSignedCertificate);
    errors2ignore << QSslError(QSslError::HostNameMismatch);
    reply->ignoreSslErrors();
  }

  loop.exec();

  //timer active if timeout didn't fire
  if (!timer.isActive()) {
    reply->abort();
    err_code = RE_TIMEOUT;
    return QByteArray();
  }

  timer.stop();
  if (reply->error() != QNetworkReply::NoError) {
    network_error = reply->error();
    CApplicationLog::Instance()->LogError("Send request network error : %s",
                              reply->errorString().toStdString().c_str());
    err_code = RE_NETWORK_ERROR;
    return QByteArray();
  }

  bool parsed = false;
  http_status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&parsed);
  return reply->readAll();
}