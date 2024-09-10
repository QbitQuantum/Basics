BOOLEAN DiskDriveQueryCache(
    _In_ HANDLE DeviceHandle
    )
{
    ULONG bufferLength;
    IO_STATUS_BLOCK isb;
    STORAGE_PROPERTY_QUERY query;
    PSTORAGE_WRITE_CACHE_PROPERTY buffer;

    query.QueryType = PropertyStandardQuery;
    query.PropertyId = StorageDeviceWriteCacheProperty;

    bufferLength = sizeof(STORAGE_WRITE_CACHE_PROPERTY);
    buffer = PhAllocate(bufferLength);
    memset(buffer, 0, bufferLength);

    if (!NT_SUCCESS(NtDeviceIoControlFile(
        DeviceHandle,
        NULL,
        NULL,
        NULL,
        &isb,
        IOCTL_STORAGE_QUERY_PROPERTY,
        &query,
        sizeof(query),
        buffer,
        bufferLength
        )))
    {
        PhFree(buffer);
        return FALSE;
    }

    bufferLength = buffer->Size;
    buffer = PhReAllocate(buffer, bufferLength);
    memset(buffer, 0, bufferLength);

    if (!NT_SUCCESS(NtDeviceIoControlFile(
        DeviceHandle,
        NULL,
        NULL,
        NULL,
        &isb,
        IOCTL_STORAGE_QUERY_PROPERTY,
        &query,
        sizeof(query),
        buffer,
        bufferLength
        )))
    {
        PhFree(buffer);
        return FALSE;
    }

    PSTORAGE_WRITE_CACHE_PROPERTY storageDescriptor = (PSTORAGE_WRITE_CACHE_PROPERTY)buffer;

    if (buffer)
    {
        PhFree(buffer);
    }

    return TRUE;
}