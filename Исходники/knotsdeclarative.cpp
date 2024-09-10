void KnotsDeclarative::taskSwitch()
{
#if defined(Q_WS_MAEMO_5)
    QDBusConnection connection = QDBusConnection::sessionBus();
    QDBusMessage message = QDBusMessage::createSignal("/","com.nokia.hildon_desktop","exit_app_view");
    connection.send(message);
#endif
}