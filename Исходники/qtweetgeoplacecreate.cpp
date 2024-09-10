/**
 *  Creates place
 *  @param name the name a place is known as
 *  @param containedWithin placeid within which the new place can be found. Be close as possible with
                           contained place
 *  @param token token found in the response from QTweetGeoSimilarPlaces
 *  @param latLong latitude and longitude
 */
void QTweetGeoPlaceCreate::create(const QString &name,
                                  const QString &containedWithin,
                                  const QString &token,
                                  const QTweetGeoCoord &latLong)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("http://api.twitter.com/1/geo/place.json");
    QUrl urlQuery(url);

    urlQuery.addEncodedQueryItem("name", QUrl::toPercentEncoding(name));
    urlQuery.addQueryItem("contained_within", containedWithin);
    urlQuery.addQueryItem("token", token);
    urlQuery.addQueryItem("lat", QString::number(latLong.latitude()));
    urlQuery.addQueryItem("long", QString::number(latLong.longitude()));

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);

    QNetworkRequest req(url);
    req.setRawHeader(AUTH_HEADER, oauthHeader);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray statusPost = urlQuery.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
    statusPost.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, statusPost);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}