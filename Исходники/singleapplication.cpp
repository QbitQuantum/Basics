QString SingleApplication::serverName() const
{
    QString serverName = QCoreApplication::applicationName();
    Q_ASSERT(!serverName.isEmpty());
#ifdef Q_WS_QWS
    serverName += QLatin1String("_qws");
#endif
#ifndef Q_OS_WIN
    serverName += QString(QLatin1String("_%1_%2")).arg(getuid()).arg(getgid());
#else
    static QString login;
    if (login.isEmpty()) {
        QT_WA({
            wchar_t buffer[256];
            DWORD bufferSize = sizeof(buffer) / sizeof(wchar_t) - 1;
            GetUserNameW(buffer, &bufferSize);
            login = QString::fromUtf16((ushort*)buffer);
        },
        {