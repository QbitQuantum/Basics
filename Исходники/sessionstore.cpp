void SessionStore::resetSession(HttpServerRequest &request) const
{
    // init variables
    QList<QByteArray> headers(request.headers().values("Cookie"));
    QByteArray newValue;

    // remove old cookies
    request.headers().remove("Cookie");

    // find cookies that don't match this store's settings
    for (int i = 0;i != headers.size();++i) {
        QList<QNetworkCookie> cookies(QNetworkCookie::parseCookies(headers[i]));

        for (int i = 0;i != cookies.size();++i) {
            if (cookies[i].name() != settings.name) {
                newValue
                    += cookies[i].toRawForm(QNetworkCookie::NameAndValueOnly)
                    + "; ";
            }
        }
    }

    if (!newValue.isEmpty()) {
        // removes the final "; "
        newValue.remove(newValue.size() - 2, 2);
    }

    // update the request headers
    request.headers().insert("Cookie", newValue);
}