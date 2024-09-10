void OsmAnd::OnlineMapRasterTileProvider_P::replyFinishedHandler( QNetworkReply* reply, const std::shared_ptr<TileEntry>& tileEntry, QEventLoop& eventLoop, QNetworkAccessManager& networkAccessManager )
{
    auto redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if(!redirectUrl.isEmpty())
    {
        reply->deleteLater();

        QNetworkRequest newRequest;
        newRequest.setUrl(redirectUrl);
        newRequest.setRawHeader("User-Agent", "OsmAnd Core");
        auto newReply = networkAccessManager.get(newRequest);
        QObject::connect(newReply, &QNetworkReply::finished,
            [this, newReply, tileEntry, &eventLoop, &networkAccessManager]()
        {
            replyFinishedHandler(newReply, tileEntry, eventLoop, networkAccessManager);
        });
        return;
    }

    // Remove current download and process pending queue
    {
        QMutexLocker scopedLock(&_currentDownloadsCounterMutex);
        _currentDownloadsCount--;
    }

    // Enqueue other downloads
    _tiles.obtainTileEntries(nullptr, [this](const std::shared_ptr<TileEntry>& entry, bool& cancel) -> bool
    {
        if(_currentDownloadsCount == owner->maxConcurrentDownloads)
        {
            cancel = true;
            return false;
        }

        if(entry->state == TileState::EnqueuedForDownload)
            obtainTileDeffered(entry);

        return false;
    });

    handleNetworkReply(reply, tileEntry);

    reply->deleteLater();
    eventLoop.exit();
}