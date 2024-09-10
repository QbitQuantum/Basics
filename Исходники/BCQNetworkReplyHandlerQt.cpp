void QNetworkReplyHandler::abort()
{
    m_resourceHandle = 0;
    if (m_reply) {
        QNetworkReply* reply = release();
        reply->abort();
        reply->deleteLater();
        deleteLater();
    }
}