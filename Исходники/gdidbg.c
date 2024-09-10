VOID
NTAPI
DbgCleanupEventList(PSLIST_HEADER pslh)
{
    PSLIST_ENTRY psle;
    PLOGENTRY pLogEntry;

    while ((psle = InterlockedPopEntrySList(pslh)))
    {
        pLogEntry = CONTAINING_RECORD(psle, LOGENTRY, sleLink);
        EngFreeMem(pLogEntry);
    }
}