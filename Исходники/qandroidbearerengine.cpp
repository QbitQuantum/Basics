void QAndroidBearerEngine::disconnectFromId(const QString &id)
{
    Q_EMIT connectionError(id, OperationNotSupported);
}