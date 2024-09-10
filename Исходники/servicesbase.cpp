void ServicesBase::abortPendingRequests()
{
    for (QMap<QNetworkReply *, CallbackType>::iterator it = _pending.begin(); it != _pending.end(); )
    {
        QNetworkReply *reply = it.key();

        if (reply)
        {
            disconnect(reply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
            disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestFinished()));

            reply->abort();
            reply->deleteLater();
        }

        _pending.remove(reply);
    }
}