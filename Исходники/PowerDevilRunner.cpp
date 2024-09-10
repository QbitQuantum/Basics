void PowerDevilRunner::initUpdateTriggers()
{
    // Also receive updates triggered through the DBus
    QDBusConnection dbus = QDBusConnection::sessionBus();
    if (dbus.interface()->isServiceRegistered("org.kde.Solid.PowerManagement")) {
        if (!dbus.connect("org.kde.Solid.PowerManagement",
                          "/org/kde/Solid/PowerManagement",
                          "org.kde.Solid.PowerManagement",
                          "profileChanged", this, SLOT(updateStatus()))) {
            kDebug() << "error!";
        }
        if (!dbus.connect("org.kde.Solid.PowerManagement",
                          "/org/kde/Solid/PowerManagement",
                          "org.kde.Solid.PowerManagement",
                          "configurationReloaded", this, SLOT(updateStatus()))) {
            kDebug() << "error!";
        }
    }
}