Q_INVOKABLE void WindowHelper::minimize()
{
#if defined(Q_OS_MAEMO)
    QDBusConnection c = QDBusConnection::sessionBus();
    QDBusMessage m = QDBusMessage::createSignal("/", "com.nokia.hildon_desktop", "exit_app_view");
    c.send(m);
    c.send(m);
#endif
}