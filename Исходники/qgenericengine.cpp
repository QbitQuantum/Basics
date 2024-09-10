void QGenericEngine::disconnectFromId(const QString &id)
{
    emit connectionError(id, OperationNotSupported);
}