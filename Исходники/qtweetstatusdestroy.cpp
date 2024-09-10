/**
 *   Destroys tweet with id
 *   @param id tweet ID
 *   @param trimUser trims users info
 *   @param includeEntities true to include node entities in response
 */
void QTweetStatusDestroy::destroy(qint64 id,
                                  bool trimUser)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1.1/statuses/destroy.json");

    QUrl urlQuery(url);

    urlQuery.addQueryItem("id", QString::number(id));

    if (trimUser)
        urlQuery.addQueryItem("trim_user", "true");

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);
    req.setRawHeader(AUTH_HEADER, oauthHeader);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postBody = urlQuery.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
    postBody.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, postBody);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}