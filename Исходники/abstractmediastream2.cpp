void AbstractMediaStream2Private::dataReady()
{
    Q_Q(AbstractMediaStream2);
    if (!eventDispatcher) {
        eventDispatcher = QAbstractEventDispatcher::instance(q->thread());
        if (!eventDispatcher) {
            pError() << "AbstractMediaStream2 needs to run in a thread with QEventLoop";
            return;
        } else {
            QObject::connect(eventDispatcher, SIGNAL(awake()), q, SLOT(_k_handleStreamEvent()), Qt::DirectConnection);
        }
    }
    eventDispatcher->wakeUp();
}