void IdleConnectionHandler::CloseIdleConnections(
    /* [in] */ Int64 idleTime)
{
    // the latest time for which connections will be closed
    AutoPtr<ISystem> system;
    CSystem::AcquireSingleton((ISystem**)&system);
    Int64 current;
    system->GetCurrentTimeMillis(&current);
    Int64 idleTimeout = current - idleTime;

    // if (log.isDebugEnabled()) {
    //     log.debug("Checking for connections, idleTimeout: "  + idleTimeout);
    // }
    AutoPtr<ISet> keySet;
    mConnectionToTimes->GetKeySet((ISet**)&keySet);
    AutoPtr<IIterator> it;
    keySet->GetIterator((IIterator**)&it);
    Boolean hasNext;
    while (it->HasNext(&hasNext), hasNext) {
        AutoPtr<IInterface> key;
        it->GetNext((IInterface**)&key);
        AutoPtr<IHttpConnection> conn = IHttpConnection::Probe(key);
        AutoPtr<IInterface> value;
        mConnectionToTimes->Get(conn, (IInterface**)&value);
        AutoPtr<TimeValues> times = (TimeValues*)(Object*)(IObject*)value.Get();
        Int64 connectionTime = times->mTimeAdded;
        if (connectionTime <= idleTimeout) {
            // if (log.isDebugEnabled()) {
            //     log.debug("Closing connection, connection time: "  + connectionTime);
            // }
            it->Remove();
            // try {
            conn->Close();
            // } catch (IOException ex) {
            //     log.debug("I/O error closing connection", ex);
            // }
        }
    }
}