bool QConnectedReplicaPrivate::waitForFinished(const QRemoteObjectPendingCall& call, int timeout)
{
    if (!call.d->watcherHelper)
        call.d->watcherHelper.reset(new QRemoteObjectPendingCallWatcherHelper);

    call.d->mutex.unlock();

    QEventLoop loop;
    loop.connect(call.d->watcherHelper.data(), SIGNAL(finished()), SLOT(quit()));
    QTimer::singleShot(timeout, &loop, SLOT(quit()));

    // enter the event loop and wait for a reply
    loop.exec(QEventLoop::ExcludeUserInputEvents | QEventLoop::WaitForMoreEvents);

    call.d->mutex.lock();

    return call.d->error != QRemoteObjectPendingCall::InvalidMessage;
}