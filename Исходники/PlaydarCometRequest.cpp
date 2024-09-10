void
PlaydarCometRequest::onReadyRead()
{
    QNetworkReply* reply = (QNetworkReply*) sender();
    QByteArray ba = reply->readAll();
    if (!m_parser->push(ba)) {
        qDebug() << "json comet parse problem";
        qDebug() << ba;
        reply->abort();     // can't recover from this
        onFinished();       // assuming abort() doesn't emit finished
    }
}