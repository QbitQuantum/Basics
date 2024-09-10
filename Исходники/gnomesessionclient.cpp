void GnomeSessionClient::slotRegisterClientFinished(QDBusPendingCallWatcher* watcher)
{
    QDBusPendingReply<QDBusObjectPath> reply = *watcher;
    watcher->deleteLater();
    if (!reply.isValid()) {
        UQ_WARNING << "Failed to register with GnomeSession:" << reply.error().message();
        return;
    }

    d->m_waitingForEndSession = true;
    QDBusConnection bus = QDBusConnection::sessionBus();
    d->m_clientPath = reply.value().path();

    bus.connect(SM_DBUS_SERVICE, d->m_clientPath, SM_CLIENT_DBUS_INTERFACE,
        "Stop", "", this, SLOT(stop()));
    bus.connect(SM_DBUS_SERVICE, d->m_clientPath, SM_CLIENT_DBUS_INTERFACE,
        "QueryEndSession", "u", this, SLOT(queryEndSession()));
    bus.connect(SM_DBUS_SERVICE, d->m_clientPath, SM_CLIENT_DBUS_INTERFACE,
        "EndSession", "u", this, SLOT(endSession()));
}