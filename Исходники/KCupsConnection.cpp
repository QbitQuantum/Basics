void KCupsConnection::notifierConnect(const QString &signal, QObject *receiver, const char *slot)
{
    QDBusConnection systemBus = QDBusConnection::systemBus();
    systemBus.connect(QString(),
                      QLatin1String("/org/cups/cupsd/Notifier"),
                      QLatin1String("org.cups.cupsd.Notifier"),
                      signal,
                      receiver,
                      slot);
}