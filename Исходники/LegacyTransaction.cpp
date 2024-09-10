void LegacyTransaction::abort(ExceptionCode& ec)
{
    if (m_state == Finishing || m_state == Finished) {
        ec = IDBDatabaseException::InvalidStateError;
        return;
    }

    m_state = Finishing;

    while (!m_requestList.isEmpty()) {
        RefPtr<LegacyRequest> request = *m_requestList.begin();
        m_requestList.remove(request);
        request->abort();
    }

    RefPtr<LegacyTransaction> selfRef = this;
    backendDB()->abort(m_id);
}