void GagImageDownloader::start()
{
    // if there is still downloads ongoing when start() is called
    // there will be big problem since m_gagList will be replaced
    Q_ASSERT(m_replyHash.isEmpty());
    foreach (const GagObject &gag, m_gagList) {
        if (gag.imageUrl().isEmpty() && gag.gifImageUrl().isEmpty())
            continue;

        if (m_downloadGIF && !gag.isGIF()) {
            qWarning("GagImageDownloader::start(): Not GIF, skip");
            continue;
        }
        const QUrl downloadImageUrl = m_downloadGIF ? gag.gifImageUrl() : gag.imageUrl();

        QNetworkReply *reply = m_networkManager->createGetRequest(downloadImageUrl, NetworkManager::Image);
        // make sure the QNetworkReply will be destroy when this object is destroyed
        reply->setParent(this);
        m_replyHash.insert(reply, gag);
        connect(reply, SIGNAL(finished()), SLOT(onFinished()));
    }

    m_imagesTotal = m_replyHash.count();
    if (m_imagesTotal > 1) {
        emit downloadProgress(0, m_imagesTotal);
    } else if (m_imagesTotal == 1) {
        connect(m_replyHash.keys().first(), SIGNAL(downloadProgress(qint64, qint64)),
                this, SIGNAL(downloadProgress(qint64,qint64)));
    } else {
        emit finished();
    }
}