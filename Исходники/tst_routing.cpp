QNetworkReply* MockGeoNetworkAccessManager::get(const QNetworkRequest& request)
{
    MockGeoNetworkReply* r = m_reply;
    m_reply = 0;
    if (r) {
        r->setRequest(request);
        r->setOperation(QNetworkAccessManager::GetOperation);
        r->setParent(0);
    }

    return r;
}