int InspectorServerRequestHandlerQt::webSocketSend(const QString& message)
{
    QByteArray payload = message.toUtf8();
    return webSocketSend(payload.data(), payload.size());
}