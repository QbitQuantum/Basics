QString QHostInfo::localHostName()
{
    // Connect to ESOCK
    RSocketServ socketServ(qt_symbianGetSocketServer());
    RHostResolver hostResolver;

    // RConnection not required to get the host name
    int err = hostResolver.Open(socketServ, KAfInet, KProtocolInetUdp);
    if (err)
        return QString();

    THostName hostName;
    err = hostResolver.GetHostName(hostName);
    if (err)
        return QString();

    hostResolver.Close();

    return qt_TDesC2QString(hostName);
}