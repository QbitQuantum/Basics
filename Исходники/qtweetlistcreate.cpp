/** Creates list
 *  @param user user id
 *  @param name the name of the list
 *  @param mode true for public list, false for private list
 *  @param description the description to give the list.
 */
void QTweetListCreate::create(qint64 user,
                              const QString &name,
                              bool mode,
                              const QString &description)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url(QString("http://api.twitter.com/1/%1/lists.json").arg(user));

    QUrl urlQuery(url);

    urlQuery.addEncodedQueryItem("name", QUrl::toPercentEncoding(name));

    if (!mode)
        urlQuery.addQueryItem("mode", "private");

    if (!description.isEmpty())
        urlQuery.addEncodedQueryItem("description", QUrl::toPercentEncoding(description));

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QByteArray postBody = urlQuery.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
    postBody.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, postBody);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}