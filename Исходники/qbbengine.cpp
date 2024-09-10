void QBBEngine::connectToId(const QString &id)
{
    Q_EMIT connectionError(id, OperationNotSupported);
}