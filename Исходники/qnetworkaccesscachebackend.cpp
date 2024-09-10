bool QNetworkAccessCacheBackend::sendCacheContents()
{
    setCachingEnabled(false);
    QAbstractNetworkCache *nc = networkCache();
    if (!nc)
        return false;

    QNetworkCacheMetaData item = nc->metaData(url());
    if (!item.isValid())
        return false;

    QNetworkCacheMetaData::AttributesMap attributes = item.attributes();
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, attributes.value(QNetworkRequest::HttpStatusCodeAttribute));
    setAttribute(QNetworkRequest::HttpReasonPhraseAttribute, attributes.value(QNetworkRequest::HttpReasonPhraseAttribute));

    // set the raw headers
    QNetworkCacheMetaData::RawHeaderList rawHeaders = item.rawHeaders();
    QNetworkCacheMetaData::RawHeaderList::ConstIterator it = rawHeaders.constBegin(),
                                                       end = rawHeaders.constEnd();
    for ( ; it != end; ++it) {
        if (it->first.toLower() == "cache-control" &&
            it->second.toLower().contains("must-revalidate")) {
            return false;
        }
        setRawHeader(it->first, it->second);
    }

    // handle a possible redirect
    QVariant redirectionTarget = attributes.value(QNetworkRequest::RedirectionTargetAttribute);
    if (redirectionTarget.isValid()) {
        setAttribute(QNetworkRequest::RedirectionTargetAttribute, redirectionTarget);
        redirectionRequested(redirectionTarget.toUrl());
    }

    // signal we're open
    metaDataChanged();

    if (operation() == QNetworkAccessManager::GetOperation) {
        QIODevice *contents = nc->data(url());
        if (!contents)
            return false;
        contents->setParent(this);
        writeDownstreamData(contents);
    }

#if defined(QNETWORKACCESSCACHEBACKEND_DEBUG)
    qDebug() << "Successfully sent cache:" << url();
#endif
    return true;
}