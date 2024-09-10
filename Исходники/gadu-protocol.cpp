void GaduProtocol::login()
{
    // TODO: create some kind of cleanup method
    if (GaduSession)
    {
        gg_free_session(GaduSession);
        GaduSession = 0;

        // here was return... do not re-add it ;)
    }

    if (SocketNotifiers)
    {
        SocketNotifiers->deleteLater();
        SocketNotifiers = 0;
    }

    auto accountData = GaduAccountData{account()};
    if (0 == accountData.uin())
    {
        connectionClosed();
        return;
    }

    GaduProxyHelper::setupProxy(
        account().useDefaultProxy() ? m_networkProxyManager->defaultProxy() : account().proxy());

    setupLoginParams();

    m_lastSentStatus = loginStatus();
    GaduSession = gg_login(&GaduLoginParams);

    cleanUpLoginParams();

    if (!GaduSession)
    {
        // gadu session can be null if DNS failed, we can try IP after that
        connectionError();
        return;
    }

    SocketNotifiers = new GaduProtocolSocketNotifiers(account(), this);
    SocketNotifiers->setGaduIMTokenService(CurrentImTokenService);
    SocketNotifiers->setGaduUserDataService(CurrentUserDataService);
    connectSocketNotifiersToServices();
    SocketNotifiers->watchFor(GaduSession);
}