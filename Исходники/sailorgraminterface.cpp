void SailorgramInterface::sendWakeUp()
{
    QDBusMessage message = QDBusMessage::createMethodCall(SailorgramInterface::INTERFACE_NAME, "/", SailorgramInterface::INTERFACE_NAME, "wakeUp");
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.send(message);
}