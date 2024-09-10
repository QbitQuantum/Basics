BTClient::BTClient(QObject *parent) : QObject (parent)
{
    QDBusConnection bus = QDBusConnection::systemBus ();
    bool success = bus.connect ("org.bluez", "", "org.bluez.Adapter", "PropertyChanged", this, SLOT (btStateChanged (QString, QDBusVariant)));
    qDebug () << success;
    if (success == false)
        qWarning("Cannot connect to org.bluez.Adapter::PropertyChanged signal.");
}