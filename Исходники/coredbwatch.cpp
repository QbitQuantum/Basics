 void connectWithDBus(const char* dbusSignal, QObject* obj, const char* slot,
                      QDBusConnection connection = QDBusConnection::sessionBus())
 {
     // connect to slave signals
     connection.connect(QString(), QLatin1String("/ChangesetRelay"),
                        QLatin1String("org.kde.digikam.DatabaseChangesetRelay"),
                        QString::fromUtf8(dbusSignal),
                        obj, slot);
     // connect to master signals
     connection.connect(QString(), QLatin1String("/ChangesetRelayForPeers"),
                        QLatin1String("org.kde.digikam.DatabaseChangesetRelay"),
                        QString::fromUtf8(dbusSignal),
                        obj, slot);
 }