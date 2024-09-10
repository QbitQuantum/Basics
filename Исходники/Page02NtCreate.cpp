static NTSTATUS MyCreateDirectory(TFileTestData * pData, POBJECT_ATTRIBUTES pObjAttr, PIO_STATUS_BLOCK pIoStatus)
{
    NTSTATUS Status;
    HANDLE SaveTransactionHandle = NULL;
    HANDLE DirectoryHandle = NULL;

    if(pData->bUseTransaction)
    {
        SaveTransactionHandle = pfnRtlGetCurrentTransaction();
        pfnRtlSetCurrentTransaction(pData->hTransaction);
    }

    Status = NtCreateFile(&DirectoryHandle,
                           FILE_ADD_FILE,
                           pObjAttr,
                           pIoStatus,
                           NULL,
                           FILE_ATTRIBUTE_DIRECTORY,
                           FILE_SHARE_READ,
                           FILE_OPEN_IF,
                           FILE_DIRECTORY_FILE,
                           NULL,
                           0);
    
    if(DirectoryHandle != NULL)
        NtClose(DirectoryHandle);

    if(pData->bUseTransaction)
    {
        pfnRtlSetCurrentTransaction(SaveTransactionHandle);
    }

    // If the directory already exists, take it as success
    return Status;
}