DataHandler::DataHandler(QObject* parent): QObject(parent) {

    connect(this, &DataHandler::credentialsInsideWallet, this, &DataHandler::startDaemon);
    QMetaObject::invokeMethod(this, "checkWallet", Qt::QueuedConnection);

    QDBusConnection dbus = QDBusConnection::sessionBus();

    dbus.connect("org.kde.kdenow", "/Event", "org.kde.kdenow.event",
                 "update", this, SLOT(onEventMapReceived(QStringList, QStringList)));
    dbus.connect("org.kde.kdenow", "/Event", "org.kde.kdenow.event",
                 "loadedEventPlugin", this, SLOT(onLoadedEventPlugin()));

    dbus.connect("org.kde.kdenow", "/Flight", "org.kde.kdenow.flight",
                 "update", this, SLOT(onFlightMapReceived(QStringList, QStringList)));
    dbus.connect("org.kde.kdenow", "/Flight", "org.kde.kdenow.flight",
                 "loadedFlightPlugin", this, SLOT(onLoadedFlightPlugin()));

    dbus.connect("org.kde.kdenow", "/Hotel", "org.kde.kdenow.hotel",
                 "update", this, SLOT(onHotelMapReceived(QStringList, QStringList)));
    dbus.connect("org.kde.kdenow", "/Hotel", "org.kde.kdenow.hotel",
                 "loadedHotelPlugin", this, SLOT(onLoadedHotelPlugin()));

    dbus.connect("org.kde.kdenow", "/Restaurant", "org.kde.kdenow.restaurant",
                 "update", this, SLOT(onRestaurantMapReceived(QStringList, QStringList)));
    dbus.connect("org.kde.kdenow", "/Restaurant", "org.kde.kdenow.restaurant",
                 "loadedRestaurantPlugin", this, SLOT(onLoadedRestaurantPlugin()));
}