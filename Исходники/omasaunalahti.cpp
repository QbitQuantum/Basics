void OmaSaunalahti::sendMessage(QNetworkAccessManager* manager, QString message) {
    if (message.toAscii().length()==0)
        return;
    this->loggedIn = false;
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));

    this->message = message;
    this->messageTime = QString("%0 %1").arg(QDate::currentDate().toString("dd.MM.yyyy")).arg(QTime::currentTime().toString("hh:mm:ss.zzz"));
    QChar *messageChar = this->message.data();
    while (!messageChar->isNull()) {
        if (messageChar->isSpace()) {
               QString chr = QString("%0").arg(QString::number( messageChar->toAscii(), 16 ).toUpper());
               if (chr.length()==1)
                   chr = "%0" + chr;
               this->message = this->message.replace(messageChar->toAscii(),chr);
         }
        ++messageChar;
    }
    QUrl url = QUrl(this->server);
    url.addQueryItem("username",this->username);
    url.addQueryItem("login","Sisään");
    url.addQueryItem("password",this->password);

    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = manager->post(request,url.toString().split("?")[1].toAscii());

    url.setEncodedQuery(QByteArray());
    url.addQueryItem("sender",this->sender);
    url.addQueryItem("recipients",this->receiver);
    url.addQueryItem("text",this->message);
    url.addQueryItem("size",QString("%0").arg(this->message.toAscii().length()));
    url.addQueryItem("send","Lähetä");
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(messageSent(QNetworkReply*)));
    reply = manager->post(request,url.toString().split("?")[1].toAscii());
}