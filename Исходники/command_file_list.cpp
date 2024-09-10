void CommandFileList::reexecuteQuery()
{
    Q_D(CommandFileList);

    QUrl url("https://www.googleapis.com/drive/v2/files");
    if (!d->query.isEmpty())
        url.addQueryItem("q", d->query);
    if (!d->fields.isEmpty())
        url.addQueryItem("fields", d->fields);
    //url.addQueryItem("maxResults","100");

    QNetworkRequest request(url);
    setRequestAccessToken(request, session()->accessToken());

    QNetworkReply* reply = session()->networkManager()->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(queryFinished()));
    reply->setParent(this);
}