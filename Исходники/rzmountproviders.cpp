UDiskProvider::UDiskProvider(QObject *parent):
    RzMountProvider(parent)
{
    QDBusConnection system = QDBusConnection::systemBus();

    if (!system.isConnected())
    {
        return;
    }

    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceAdded",
                    this,
                    SLOT(dbusDeviceAdded(QDBusObjectPath)));

    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceRemoved",
                    this,
                    SLOT(dbusDeviceRemoved(QDBusObjectPath)));

    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceChanged",
                    this,
                    SLOT(dbusDeviceChanged(QDBusObjectPath)));

    mIsValid = true;
}