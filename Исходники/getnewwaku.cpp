void NicoLiveManager::getNewWakuAPI(const int type, QString liveNum)
{
  if (type == 2) {
    if (!nwin->isSetNecessary()) {
      mwin->insLog("NicoLiveManager::getNewWakuAPI type" + QString::number(type) + " no necessary item(s)");
      QMessageBox::information(mwin, "Viqo", QStringLiteral("設定されていない必須項目があります"));
      return;
    }
    if (!nwin->isTwitterTagValid()) {
      mwin->insLog("NicoLiveManager::getNewWakuAPI type" + QString::number(type) + " twitter tag must start with \"#\"");
      QMessageBox::information(mwin, "Viqo", QStringLiteral("ツイッタータグは # で始めてください"));
      return;
    }
  }

  if (mNewWaku!=nullptr) mNewWaku->deleteLater();
  mNewWaku = new QNetworkAccessManager(this);

  QHttpMultiPart *multiPart;
  if (type > 2) {
    multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->setParent(mNewWaku);
  } else {
    multiPart = nullptr;
  }

  if (type == 0) {
    connect(mNewWaku, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(newWakuNewReuseFinished(QNetworkReply*)));
  } else if (type == 1) {