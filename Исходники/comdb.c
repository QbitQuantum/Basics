LONG
WINAPI
ComDBResizeDatabase(IN HCOMDB hComDB,
                    IN DWORD NewSize)
{
    PCOMDB pComDB;
    PBYTE pBitmap = NULL;
    DWORD dwSize;
    DWORD dwNewSize;
    DWORD dwType;
    LONG lError;

    TRACE("ComDBResizeDatabase(%p %lu)\n", hComDB, NewSize);

    if (hComDB == INVALID_HANDLE_VALUE ||
        hComDB == NULL ||
        (NewSize & BITMAP_SIZE_INVALID_BITS))
        return ERROR_INVALID_PARAMETER;

    pComDB = (PCOMDB)hComDB;

    /* Wait for the mutex */
    WaitForSingleObject(pComDB->hMutex, INFINITE);

    /* Get the required bitmap size */
    lError = RegQueryValueExW(pComDB->hKey,
                              L"ComDB",
                              NULL,
                              &dwType,
                              NULL,
                              &dwSize);
    if (lError != ERROR_SUCCESS)
        goto done;

    /* Check the size limits */
    if (NewSize > COMDB_MAX_PORTS_ARBITRATED ||
        NewSize <= dwSize * BITS_PER_BYTE)
    {
        lError = ERROR_BAD_LENGTH;
        goto done;
    }

    /* Calculate the new bitmap size */
    dwNewSize = NewSize / BITS_PER_BYTE;

    /* Allocate the new bitmap */
    pBitmap = HeapAlloc(GetProcessHeap(),
                        HEAP_ZERO_MEMORY,
                        dwSize);
    if (pBitmap == NULL)
    {
        ERR("Failed to allocate the bitmap!\n");
        lError = ERROR_ACCESS_DENIED;
        goto done;
    }

    /* Read the current bitmap */
    lError = RegQueryValueExW(pComDB->hKey,
                              L"ComDB",
                              NULL,
                              &dwType,
                              pBitmap,
                              &dwSize);
    if (lError != ERROR_SUCCESS)
        goto done;

    /* Write the new bitmap */
    lError = RegSetValueExW(pComDB->hKey,
                            L"ComDB",
                            0,
                            REG_BINARY,
                            pBitmap,
                            dwNewSize);

done:;
    /* Release the mutex */
    ReleaseMutex(pComDB->hMutex);

    if (pBitmap != NULL)
        HeapFree(GetProcessHeap(), 0, pBitmap);

    return lError;
}