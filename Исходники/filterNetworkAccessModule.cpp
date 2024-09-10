QNetworkReply *filterNetworkAccessModule::Get()
{
    QUrl url(this->requestURL);
    QNetworkRequest req(url);

    this->reply = netManager->get(req);

    connect(reply, SIGNAL(finished()), this, SLOT(networkReply()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));

    {
        QEventLoop loop;
        loop.connect(this, SIGNAL(dataProcessed()), SLOT(quit()));
//        std::cout << "...in event loop..." << std::endl;
        loop.exec();

//        std::cout << "EVENT LOOP HAS EXITED" << std::endl;
    }
    return this->reply;
}