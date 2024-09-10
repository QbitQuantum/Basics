IDBServer::IDBServer()
{
    Locker<Lock> locker(m_databaseThreadCreationLock);
    m_threadID = createThread(IDBServer::databaseThreadEntry, this, "IndexedDatabase Server");
}