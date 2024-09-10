bool SafeApiFactory::authUser(QString login, QString password)
{
    QEventLoop loop;
    auto api = new SafeApi(this->host);
    bool success;

    connect(api, &SafeApi::authUserComplete, [&](ulong id, QString user_id){
        qDebug() << "Authentication complete (user id:" << user_id << ")";
        this->sharedState = api->state();
        this->m_login = login;
        this->password = password;
        success = true;
        loop.exit();
    });
    connect(api, &SafeApi::errorRaised, [&](ulong id, quint16 code, QString text){
        this->sharedState.clear();
        api = NULL;
        qWarning() << "Authentication error:" << text;
        loop.exit();
    });

    api->authUser(login, password);
    loop.exec();
    return success;
}