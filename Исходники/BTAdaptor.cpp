void
BTAdaptor::searchBtDevices ()
{
    // Connect to the signal DeviceFound to obtain the list of devices
    QDBusConnection bus = QDBusConnection::systemBus ();
    bool success = bus.connect ("org.bluez",
                                mAdapterPath,
                                "org.bluez.Adapter",
                                "DeviceFound",
                                this,
                                SLOT (deviceFound(QString,QMap<QString,QVariant>)));

    if (!success)
    {
        qDebug() << "Failure in connecting dbus signal";
        return;
    }
    
    QDBusMessage msg = QDBusMessage::createMethodCall ("org.bluez",
                                                       mAdapterPath,
                                                       "org.bluez.Adapter",
                                                       "StartDiscovery");

    QDBusMessage reply = bus.call (msg);
    if (reply.type () == QDBusMessage::ErrorMessage)
    {
        qWarning() << "Error in dbus call to search for devices";
        return ;
    }
}