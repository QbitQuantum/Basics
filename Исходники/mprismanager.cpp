MprisManager::MprisManager(QObject *parent)
    : QObject(parent)
    , m_singleService(false)
    , m_playbackStatusMapper(new QSignalMapper(this))
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
//        qmlInfo(this) << "Failed attempting to connect to DBus";
        return;
    }

    connection.connect(dBusService, dBusObjectPath, dBusInterface, dBusNameOwnerChangedSignal,
                       QStringList(), QString(),
                       this, SLOT(onNameOwnerChanged(QString, QString, QString)));

    QStringList serviceNames = connection.interface()->registeredServiceNames();
    QStringList::const_iterator i = serviceNames.constBegin();
    while (i != serviceNames.constEnd()) {
        QRegExp rx(mprisNameSpace);
        rx.setPatternSyntax(QRegExp::Wildcard);
        if (rx.exactMatch(*i)) {
            onServiceAppeared(*i);
        }

        ++i;
    }
}