void WLQuery::Process()
{
    if (Configuration::HuggleConfiguration->GlobalConfig_Whitelist.isEmpty())
    {
        // there is no whitelist in config for this wiki
        Syslog::HuggleLogs->ErrorLog("Unable to process WL request, there is no whitelist server defined");
        this->Result = new QueryResult();
        this->Result->SetError("Invalid URL");
        this->Status = Huggle::StatusInError;
        return;
    }
    this->StartTime = QDateTime::currentDateTime();
    this->Status = StatusProcessing;
    this->Result = new QueryResult();
    QUrl url(Configuration::HuggleConfiguration->GlobalConfig_Whitelist
             + "?action=read&wp=" + this->GetSite()->WhiteList);
    switch (this->Type)
    {
        case WLQueryType_ReadWL:
            break;
        case WLQueryType_SuspWL:
            url = QUrl(Configuration::HuggleConfiguration->GlobalConfig_Whitelist +
                       "susp.php?action=insert&" + this->Parameters);
            break;
        case WLQueryType_WriteWL:
            url = QUrl(Configuration::HuggleConfiguration->GlobalConfig_Whitelist + "?action=save&user="******"huggle_" + Configuration::HuggleConfiguration->SystemConfig_Username) +
                      "&wp=" + this->GetSite()->WhiteList);
            break;
    }
    QString params = "";
    QByteArray data;
    if (this->Type == WLQueryType_WriteWL)
    {
        QString whitelist = "";
        int p = 0;
        while (p < this->GetSite()->GetProjectConfig()->NewWhitelist.count())
        {
            if (!this->GetSite()->GetProjectConfig()->NewWhitelist.at(p).isEmpty())
            {
                whitelist += this->GetSite()->GetProjectConfig()->NewWhitelist.at(p) + "|";
            }
            p++;
        }
        if (whitelist.endsWith("|"))
        {
            whitelist = whitelist.mid(0, whitelist.length() - 1);
        }
        whitelist += "||EOW||";
        params = "wl=" + QUrl::toPercentEncoding(whitelist);
        data = params.toUtf8();
        long size = (long)data.size();
        Syslog::HuggleLogs->DebugLog("Sending whitelist data of size: " + QString::number(size) + " byte to " + this->GetSite()->Name);
    }
    QNetworkRequest request(url);
    if (this->Type == WLQueryType_ReadWL)
    {
        this->networkReply = Query::NetworkManager->get(request);
    } else
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        this->networkReply = Query::NetworkManager->post(request, data);
    }
    QObject::connect(this->networkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(WriteProgress(qint64,qint64)));
    QObject::connect(this->networkReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(WriteProgress(qint64,qint64)));
    QObject::connect(this->networkReply, SIGNAL(finished()), this, SLOT(Finished()));
    QObject::connect(this->networkReply, SIGNAL(readyRead()), this, SLOT(ReadData()));
}