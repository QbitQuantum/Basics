void SearchEnginesManager::addEngine(const QUrl &url)
{
    ENSURE_LOADED;

    if (!url.isValid()) {
        return;
    }

    qApp->setOverrideCursor(Qt::WaitCursor);

    QNetworkReply* reply = mApp->networkManager()->get(QNetworkRequest(url));
    reply->setParent(this);
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}