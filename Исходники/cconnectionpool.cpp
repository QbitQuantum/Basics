HRESULT CConnectionPool::Return(HANDLE connection)
{
    HRESULT hr;
    PCONNECTION_ENTRY entry = NULL;

    if (this->count >= this->maxPoolSize)
    {
        CloseHandle(connection);
    }
    else
    {
        ErrorIf(NULL == (entry = (PCONNECTION_ENTRY)_aligned_malloc(sizeof(CONNECTION_ENTRY), MEMORY_ALLOCATION_ALIGNMENT)), ERROR_NOT_ENOUGH_MEMORY);
        entry->connection = connection;
        entry->timestamp = GetTickCount();
        InterlockedPushEntrySList(this->list, &(entry->listEntry));
        InterlockedIncrement(&this->count);
    }

    return S_OK;
Error:

    return hr;
}