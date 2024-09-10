  std::pair<QNetworkReply::NetworkError, QString> NetworkProxyDialog::testProxyConnection(const QNetworkProxy &t_proxy, QWidget *t_parent)
  {
    QProgressDialog dlg("Verifying Proxy Connection", "Cancel",0, 1000, t_parent);
    dlg.setWindowModality(Qt::WindowModal);
    dlg.setValue(0);
    dlg.setMinimumDuration(1000);

    QNetworkAccessManager nam;
    nam.setProxy(t_proxy);
    QNetworkReply *head = nam.head(QNetworkRequest(QUrl("https://bcl.nrel.gov/")));

    if (!head) return std::make_pair(QNetworkReply::UnknownNetworkError, QString("Unknown error creating connection to proxy."));

    boost::posix_time::ptime start = boost::posix_time::microsec_clock::universal_time();
    while ( !head->isFinished()
            && (boost::posix_time::microsec_clock::universal_time() - start).total_milliseconds() < 10000
            && !dlg.wasCanceled())
    {
      int time = (boost::posix_time::microsec_clock::universal_time() - start).total_milliseconds();
      dlg.setValue(time);
      if (time >= 950 && dlg.maximum() < 10000)
      {
        dlg.setMaximum(10000);
      }
    }
    dlg.reset();
    Application::instance().processEvents();

    head->deleteLater();

    if (!head->isFinished()) 
    {
      head->abort();
      return std::make_pair(QNetworkReply::TimeoutError, QString("Timed out while attempting to verify proxy connection"));
    }

    LOG(Debug, " errorString from proxy test " << toString(head->errorString()) << " " << head->error());

    return std::make_pair(head->error(), head->errorString());
  }