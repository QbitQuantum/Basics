/**
 *   Sends direct message
 *   @param user The ID of the user who should receive the direct message.
 *   @param text The text of direct message
 *   @param includeEntities When set to true each tweet will include a node called "entities,"
 */
void QTweetDirectMessageNew::post(const QString &screenName, const QString &text, bool includeEntities)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1/direct_messages/new.json");

    QUrl urlQuery(url);

    urlQuery.addEncodedQueryItem("screen_name", QUrl::toPercentEncoding(screenName));
    urlQuery.addEncodedQueryItem("text", QUrl::toPercentEncoding(text));

    if (includeEntities)
        urlQuery.addQueryItem("include_entities", "true");

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);
    req.setRawHeader(AUTH_HEADER, oauthHeader);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postBody = urlQuery.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
    postBody.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, postBody);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}