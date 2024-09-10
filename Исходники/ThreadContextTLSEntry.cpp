ThreadContextId ThreadContextTLSEntry::GetCurrentThreadContextId()
{
    ThreadContextTLSEntry * entry = ENTRY_FOR_CURRENT_THREAD();
    if (entry != NULL && entry->GetThreadContext() != NULL)
    {
        return (ThreadContextId)entry->GetThreadContext();
    }

    return NoThreadContextId;
}