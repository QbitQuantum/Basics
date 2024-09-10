void IDBDatabaseBackend::runIntVersionChangeTransaction(PassRefPtr<IDBCallbacks> prpCallbacks, PassRefPtr<IDBDatabaseCallbacks> prpDatabaseCallbacks, int64_t transactionId, int64_t requestedVersion)
{
    RefPtr<IDBCallbacks> callbacks = prpCallbacks;
    RefPtr<IDBDatabaseCallbacks> databaseCallbacks = prpDatabaseCallbacks;
    ASSERT(callbacks);
    for (DatabaseCallbacksSet::const_iterator it = m_databaseCallbacksSet.begin(); it != m_databaseCallbacksSet.end(); ++it) {
        // Front end ensures the event is not fired at connections that have closePending set.
        if (*it != databaseCallbacks)
            (*it)->onVersionChange(m_metadata.version, requestedVersion, IndexedDB::NullVersion);
    }
    // The spec dictates we wait until all the version change events are
    // delivered and then check m_databaseCallbacks.empty() before proceeding
    // or firing a blocked event, but instead we should be consistent with how
    // the old setVersion (incorrectly) did it.
    // FIXME: Remove the call to onBlocked and instead wait until the frontend
    // tells us that all the blocked events have been delivered. See
    // https://bugs.webkit.org/show_bug.cgi?id=71130
    if (connectionCount())
        callbacks->onBlocked(m_metadata.version);
    // FIXME: Add test for m_runningVersionChangeTransaction.
    if (m_runningVersionChangeTransaction || connectionCount()) {
        m_pendingOpenCalls.append(IDBPendingOpenCall::create(*callbacks, *databaseCallbacks, transactionId, requestedVersion));
        return;
    }

    Vector<int64_t> objectStoreIds;
    createTransaction(transactionId, databaseCallbacks, objectStoreIds, IndexedDB::TransactionVersionChange);
    RefPtr<IDBTransactionBackend> transaction = m_transactions.get(transactionId);

    transaction->scheduleVersionChangeOperation(transactionId, requestedVersion, callbacks, databaseCallbacks, m_metadata);

    ASSERT(!m_pendingSecondHalfOpen);
    m_databaseCallbacksSet.add(databaseCallbacks);
}