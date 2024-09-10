INT
WSAAPI
WsSetupCatalogProtection(IN HKEY CatalogKey,
                         IN HANDLE CatalogEvent,
                         OUT LPDWORD UniqueId)
{
    INT ErrorCode;
    HKEY RegistryKey;
    DWORD NewUniqueId;
    CHAR KeyBuffer[32];
    DWORD RegType = REG_DWORD;
    DWORD RegSize = sizeof(DWORD);

    /* Start loop */
    do
    {
#if 0
        /* Ask for notifications */
        ErrorCode = RegNotifyChangeKeyValue(CatalogKey,
                                            FALSE,
                                            REG_NOTIFY_CHANGE_NAME,
                                            CatalogEvent,
                                            TRUE);
        if (ErrorCode != ERROR_SUCCESS)
        {
            /* Normalize error code */
            ErrorCode = WSASYSCALLFAILURE;
            break;
        }
#endif

        /* Read the current ID */
        ErrorCode = RegQueryValueEx(CatalogKey,
                                    "Serial_Access_Num",
                                    0,
                                    &RegType,
                                    (LPBYTE)&NewUniqueId,
                                    &RegSize);
        if (ErrorCode != ERROR_SUCCESS)
        {
            /* Critical failure */
            ErrorCode = WSASYSCALLFAILURE;
            break;
        }

        /* Try to open it for writing */
        sprintf(KeyBuffer, "%8.8lX", NewUniqueId);
        ErrorCode = RegOpenKeyEx(CatalogKey,
                                 KeyBuffer,
                                 0,
                                 MAXIMUM_ALLOWED,
                                 &RegistryKey);

        /* If the key doesn't exist or is being delete, that's ok for us */
        if ((ErrorCode == ERROR_FILE_NOT_FOUND) ||
            (ErrorCode == ERROR_KEY_DELETED))
        {
            /* Set success and return the new ID */
            ErrorCode = ERROR_SUCCESS;
            *UniqueId = NewUniqueId;
            break;
        }
        else if (ErrorCode != ERROR_SUCCESS)
        {
            /* Any other failure is bad */
            ErrorCode = WSASYSCALLFAILURE;
            break;
        }

        /* If we could actually open the key, someone is using it :/ */
        ErrorCode = RegCloseKey(RegistryKey);

        /* In case we break out prematurely */
        ErrorCode = WSANO_RECOVERY;

        /* Keep looping until they let go of the registry writing */
    } while (!WaitForSingleObject(CatalogEvent, 180 * 1000));

    /* Return error code */
    return ErrorCode;
}