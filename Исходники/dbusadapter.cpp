DbusAdapter::DbusAdapter(QObject *parent) :
    QObject(parent)
{
    QDBusConnection systemConn = QDBusConnection::systemBus();
    systemConn.connect("org.ofono", "/ril_0", "org.ofono.VoiceCallManager", "CallAdded",
                         this, SLOT(_phoneCall(QDBusMessage)));
    systemConn.connect("org.ofono", "/ril_0", "org.ofono.MessageManager", "IncomingMessage",
                         this, SLOT(_smsReceived(QDBusMessage)));

    QDBusConnection sessionConn = QDBusConnection::sessionBus();
    sessionConn.connect("", "/", "org.coderus.harbour_mitakuuluu_server", "messageReceived",
                        this, SLOT(_mitakuuluuMessageReceived(QDBusMessage)));

    qDebug() << "Setting up hack for getting notifications...";
    // The inspiration for this hack was taken from: http://stackoverflow.com/questions/22592042/qt-dbus-monitor-method-calls
    sessionConn.registerObject("/org/freedesktop/Notifications", this, QDBusConnection::ExportAllSlots);
    QString matchString = "interface='org.freedesktop.Notifications',member='Notify',type='method_call',eavesdrop='true'";
    QDBusInterface busInterface("org.freedesktop.DBus", "/org/freedesktop/DBus",
                                "org.freedesktop.DBus");
    busInterface.call("AddMatch", matchString);
    qDebug() << "Leaving constructor...";
}