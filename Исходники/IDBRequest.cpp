void IDBRequest::onSuccess(PassRefPtr<IDBTransactionBackendInterface> prpBackend)
{
    IDB_TRACE("IDBRequest::onSuccess(IDBTransaction)");
    RefPtr<IDBTransactionBackendInterface> backend = prpBackend;

    if (m_contextStopped || !scriptExecutionContext()) {
        // Should only be null in tests.
        if (backend.get())
            backend->abort();
        return;
    }
    if (!shouldEnqueueEvent())
        return;

    RefPtr<IDBTransaction> frontend = IDBTransaction::create(scriptExecutionContext(), backend, IDBTransaction::VERSION_CHANGE, m_source->idbDatabase().get());
    backend->setCallbacks(frontend.get());
    m_transaction = frontend;

    ASSERT(m_source->type() == IDBAny::IDBDatabaseType);
    ASSERT(m_transaction->isVersionChange());

    m_result = IDBAny::create(frontend.release());
    enqueueEvent(createSuccessEvent());
}