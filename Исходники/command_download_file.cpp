void CommandDownloadFile::reexecuteQuery()
{
    Q_D(CommandDownloadFile);
    QNetworkRequest request( d->downloadUrl );
    setRequestAccessToken(request, session()->accessToken());
    QNetworkReply* reply = session()->networkManager()->get(request);
    reply->setReadBufferSize(d->bufferSize);
    connect(reply, SIGNAL(finished()), SLOT(requestFinished()));
    connect(reply, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), SIGNAL(progress(qint64,qint64)));
    reply->setParent(this);
}