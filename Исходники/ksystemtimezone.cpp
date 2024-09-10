KSystemTimeZones::KSystemTimeZones()
  : d(0)
{
#if !defined(TIMED_SUPPORT) && !defined(KCALCORE_FOR_MEEGO)
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.connect(QString(), QString(), KTIMEZONED_DBUS_IFACE, "configChanged", this, SLOT(configChanged()));
    dbus.connect(QString(), QString(), KTIMEZONED_DBUS_IFACE, "zonetabChanged", this, SLOT(zonetabChanged(QString)));
    // No need to connect to definitionChanged() - see comments in zoneDefinitionChanged()
    //dbus.connect(QString(), QString(), KTIMEZONED_DBUS_IFACE, "definitionChanged", this, SLOT(zoneDefinitionChanged(QString)));
#endif
}