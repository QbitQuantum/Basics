void DeclarativeDBusInterface::call(const QString &method, const QJSValue &arguments)
{
    QVariantList dbusArguments = argumentsFromScriptValue(arguments);

    QDBusMessage message = QDBusMessage::createMethodCall(
                m_service,
                m_path,
                m_interface,
                method);
    message.setArguments(dbusArguments);

    QDBusConnection conn = DeclarativeDBus::connection(m_bus);

    if (!conn.send(message))
        qmlInfo(this) << conn.lastError();
}