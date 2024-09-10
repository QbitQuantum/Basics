UdisksManager::UdisksManager(QObject *parent)
    : QObject(parent)
{
    QDBusConnection system = QDBusConnection::systemBus();

    if (!system.isConnected())
    {
        emit error(tr("Cannot connect to Udisks daemon"));
    }

    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceAdded",
                    this,
                    SLOT(onDeviceAdded(QDBusObjectPath)));
    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceRemoved",
                    this,
                    SLOT(onDeviceRemoved(QDBusObjectPath)));
    system.connect("org.freedesktop.UDisks",
                    "/org/freedesktop/UDisks",
                    "org.freedesktop.UDisks",
                    "DeviceChanged",
                    this,
                    SLOT(onDeviceChanged(QDBusObjectPath)));

    QDBusInterface devEnum("org.freedesktop.UDisks",
                           "/org/freedesktop/UDisks",
                           "org.freedesktop.UDisks",
                           QDBusConnection::systemBus());

    QDBusMessage enumRes = devEnum.call("EnumerateDevices");
    // TODO/FIXME: error checking
//    if (enumRes.type() == QDBusMessage::ErrorMessage)
//    {
//        fprintf(stderr, "ERROR: Can't call EnumerateDevices\n");
//        fprintf(stderr, "       %s : %s\n", qPrintable(enumRes.errorName()), qPrintable(enumRes.errorMessage()));
//    }
//
//    if (enumRes.type() != QDBusMessage::ReplyMessage || !enumRes.arguments().at(0).canConvert<QDBusArgument>())
//    {
//        fprintf(stderr, "ERROR: Unexpected result type of EnumerateDevices call\n");
//    }
//
    const QDBusArgument enumArg = enumRes.arguments().at(0).value<QDBusArgument>();
//    if (enumArg.currentType() != QDBusArgument::ArrayType)
//    {
//        fprintf(stderr, "ERROR: Unexpected argument type of EnumerateDevices call\n");
//    }

    enumArg.beginArray();
    while (!enumArg.atEnd())
    {
        addDevice(qdbus_cast<QDBusObjectPath>(enumArg));
    }
    enumArg.endArray();
}