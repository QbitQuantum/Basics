Client* ClientConnectionSet::FindPlayer(PID playerID)
{
    CS::Threading::RecursiveMutexScopedLock lock(mutex);
    AddressHash::GlobalIterator it(addrHash.GetIterator());

    while(it.HasNext())
    {
        Client* p = it.Next();
        if(p->GetPID() == playerID)
            return p;
    }

    return NULL;
}