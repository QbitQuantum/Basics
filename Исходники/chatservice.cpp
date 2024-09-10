void ChatService::startLoginRequest()
{
    _buddylist_poll_timer->stop();
    
    qDebug() << _network->cookieJar()->cookiesForUrl(QUrl(FACEBOOK_URL)).count() << " cookies";
    QList<QNetworkCookie> cookies;
    
    QMap<QString, QString> params;
    QUrl url(FACEBOOK_LOGIN_URL);

    QNetworkCookie cookie;
    cookie.setDomain(".facebook.com");
    cookie.setPath("/");

    // facebook uses this cookie to test for cookie support
    // if we dont set it it thinks we don't support cookies.
    cookie.setName("test_cookie");
    cookie.setValue("1");
    cookies << cookie;

    cookie.setName("isfbe");
    cookie.setValue("false");
    cookies << cookie;

    _network->cookieJar()->setCookiesFromUrl(cookies, QUrl(FACEBOOK_URL));

    qDebug() << _network->cookieJar()->cookiesForUrl(QUrl(FACEBOOK_URL)).count() << " cookies";

    // it seems those are not really needed, until I figure what
    // are they for
    //params.insert("md5pass", "0");
    //params.insert("noerror", "1");

    params.insert("email", _login);
    params.insert("pass", _password);
    params.insert("persistent", "1");
    params.insert("login", "Login");
    params.insert("charset_test", "€,´,€,´,水,Д,Є");

    QString data = encodePostParams(params);
    qDebug() << data;

    QNetworkReply *reply = _network->post(QNetworkRequest(url), data.toAscii());
    reply->setParent(this);
    
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(slotLoginRequestFinished()));
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotLoginRequestError(QNetworkReply::NetworkError)));
}