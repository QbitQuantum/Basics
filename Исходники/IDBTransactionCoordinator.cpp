void IDBTransactionCoordinator::abort(int id)
{
    ASSERT(m_idMap.contains(id));
    RefPtr<IDBTransactionBackendInterface> transaction = m_idMap.get(id);
    ASSERT(transaction);
    m_transactionQueue.remove(transaction.get());
    m_idMap.remove(id);
    transaction->abort();
    // FIXME: this will change once we have transactions actually running.
}