void CWizDocumentStatusCheckThread::downloadData(const QString& strUrl)
{
    QNetworkAccessManager net;
    QNetworkReply* reply = net.get(QNetworkRequest(strUrl));

    QEventLoop loop;
    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    if (reply->error()) {
        Q_EMIT checkFinished(QString(), QStringList());
        reply->deleteLater();
        return;
    }

    rapidjson::Document d;
    d.Parse<0>(reply->readAll().constData());
    if (d.IsArray())
    {
        QStringList strList;
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QTextDecoder* encoder = codec->makeDecoder();
        for (rapidjson::SizeType i = 0; i < d.Size(); i++)
        {
            const rapidjson::Value& u = d[i];
            strList.append(encoder->toUnicode(u.GetString(), u.GetStringLength()));
        }
        //
        {
            QMutexLocker lock(&m_mutexWait);
            if (strUrl.indexOf(m_strGUID) != -1)
            {
                emit checkFinished(m_strGUID, strList);
            }
            else
            {
                needRecheck();
            }
        }
        reply->deleteLater();
        return;
    }
    Q_EMIT checkFinished(QString(), QStringList());
    reply->deleteLater();
}