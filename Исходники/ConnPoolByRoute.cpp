void ConnPoolByRoute::DeleteClosedConnections()
{
    ILock::Probe(mPoolLock)->Lock();
    // try {
    AutoPtr<IIterator> iter;
    mFreeConnections->GetIterator((IIterator**)&iter);
    Boolean hasNext;
    while(iter->HasNext(&hasNext), hasNext) {
        AutoPtr<IInterface> value;
        iter->GetNext((IInterface**)&value);
        AutoPtr<BasicPoolEntry> entry = reinterpret_cast<BasicPoolEntry*>(value->Probe(EIID_BasicPoolEntry));
        Boolean isOpen;
        if (IHttpConnection::Probe(entry->GetConnection())->IsOpen(&isOpen), !isOpen) {
            iter->Remove();
            DeleteEntry(entry);
        }
    }
    // } finally {
    //     poolLock.UnLock();
    // }
    ILock::Probe(mPoolLock)->UnLock();
}