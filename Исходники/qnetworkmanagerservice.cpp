bool QNetworkManagerInterfaceDeviceWireless::setConnections()
{
    if(!isValid() )
        return false;

    QDBusConnection dbusConnection = QDBusConnection::systemBus();
    bool allOk = false;
    delete nmDBusHelper;
    nmDBusHelper = new QNmDBusHelper(this);
    connect(nmDBusHelper, SIGNAL(pathForPropertiesChanged(QString,QMap<QString,QVariant>)),
            this,SIGNAL(propertiesChanged(QString,QMap<QString,QVariant>)));

    connect(nmDBusHelper, SIGNAL(pathForAccessPointAdded(QString,QDBusObjectPath)),
            this,SIGNAL(accessPointAdded(QString,QDBusObjectPath)));

    connect(nmDBusHelper, SIGNAL(pathForAccessPointRemoved(QString,QDBusObjectPath)),
            this,SIGNAL(accessPointRemoved(QString,QDBusObjectPath)));

    if(!dbusConnection.connect(QLatin1String(NM_DBUS_SERVICE),
                              d->path,
                              QLatin1String(NM_DBUS_INTERFACE_DEVICE_WIRELESS),
                              QLatin1String("AccessPointAdded"),
                              nmDBusHelper, SLOT(slotAccessPointAdded(QDBusObjectPath)))) {
        allOk = true;
    }


    if(!dbusConnection.connect(QLatin1String(NM_DBUS_SERVICE),
                              d->path,
                              QLatin1String(NM_DBUS_INTERFACE_DEVICE_WIRELESS),
                              QLatin1String("AccessPointRemoved"),
                              nmDBusHelper, SLOT(slotAccessPointRemoved(QDBusObjectPath)))) {
        allOk = true;
    }


    if(!dbusConnection.connect(QLatin1String(NM_DBUS_SERVICE),
                              d->path,
                              QLatin1String(NM_DBUS_INTERFACE_DEVICE_WIRELESS),
                              QLatin1String("PropertiesChanged"),
                              nmDBusHelper,SLOT(slotPropertiesChanged(QMap<QString,QVariant>)))) {
        allOk = true;
    }

    return allOk;
}