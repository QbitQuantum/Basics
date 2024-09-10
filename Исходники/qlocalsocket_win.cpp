void QLocalSocket::close()
{
    Q_D(QLocalSocket);
    if (state() == UnconnectedState)
        return;

    QIODevice::close();
    d->state = ClosingState;
    emit stateChanged(d->state);
    if (!d->pipeClosed)
        emit readChannelFinished();
    d->serverName = QString();
    d->fullServerName = QString();

    if (state() != UnconnectedState && bytesToWrite() > 0) {
        disconnectFromServer();
        return;
    }
    d->readSequenceStarted = false;
    d->pendingReadyRead = false;
    d->pipeClosed = false;
    DisconnectNamedPipe(d->handle);
    CloseHandle(d->handle);
    d->handle = INVALID_HANDLE_VALUE;
    ResetEvent(d->overlapped.hEvent);
    d->state = UnconnectedState;
    emit stateChanged(d->state);
    emit disconnected();
    if (d->pipeWriter) {
        delete d->pipeWriter;
        d->pipeWriter = 0;
    }
}