Authorization::Authorization(const QString &login, const QString &password) :
    QObject(NULL),
    m_login(login),
    m_password(password)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart loginPart;
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
    loginPart.setBody(m_login.toLatin1());

    QHttpPart passPart;
    passPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pass\""));
    passPart.setBody(m_password.toLatin1());

    multiPart->append(loginPart);
    multiPart->append(passPart);

    QUrl url("http://freedomsex.net/login.php");
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(test_answer(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
}