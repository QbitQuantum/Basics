void IDBTransaction::abort(ExceptionState& exceptionState)
{
    if (m_state == Finishing || m_state == Finished) {
        exceptionState.throwDOMException(InvalidStateError, IDBDatabase::transactionFinishedErrorMessage);
        return;
    }

    m_state = Finishing;

    if (m_contextStopped)
        return;

    while (!m_requestList.isEmpty()) {
        IDBRequest* request = *m_requestList.begin();
        m_requestList.remove(request);
        request->abort();
    }

    if (backendDB())
        backendDB()->abort(m_id);
}