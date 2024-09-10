/********************************************************************
 WcaCaScriptReadAsCustomActionData() - read the ca script into a format
                                       that is useable by other CA data
                                       functions.

********************************************************************/
extern "C" HRESULT WIXAPI WcaCaScriptReadAsCustomActionData(
    __in WCA_CASCRIPT_HANDLE hScript,
    __out LPWSTR* ppwzCustomActionData
    )
{
    HRESULT hr = S_OK;
    LARGE_INTEGER liScriptSize = { 0 };
    BYTE* pbData = NULL;
    DWORD cbData = 0;

    if (!::GetFileSizeEx(hScript->hScriptFile, &liScriptSize))
    {
        ExitWithLastError(hr, "Failed to get size of ca script file.");
    }

    if (0 != liScriptSize.HighPart || 0 != (liScriptSize.LowPart % sizeof(WCHAR)))
    {
        hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
        ExitOnFailure(hr, "Invalid data read from ca script.");
    }

    cbData = liScriptSize.LowPart;
    pbData = static_cast<BYTE*>(MemAlloc(cbData, TRUE));
    ExitOnNull(pbData, hr, E_OUTOFMEMORY, "Failed to allocate memory to read in ca script.");

    if (INVALID_SET_FILE_POINTER == ::SetFilePointer(hScript->hScriptFile, 0, NULL, FILE_BEGIN))
    {
        ExitWithLastError(hr, "Failed to reset to beginning of ca script.");
    }

    DWORD cbTotalRead = 0;
    DWORD cbRead = 0;
    do
    {
        if (!::ReadFile(hScript->hScriptFile, pbData + cbTotalRead, cbData - cbTotalRead, &cbRead, NULL))
        {
            ExitWithLastError(hr, "Failed to read from ca script.");
        }

        cbTotalRead += cbRead;
    } while (cbRead && cbTotalRead < cbData);

    if (cbTotalRead != cbData)
    {
        hr = E_UNEXPECTED;
        ExitOnFailure(hr, "Failed to completely read ca script.");
    }

    // Add one to the allocated space because the data stored in the script is not
    // null terminated.  After copying the memory over, we'll ensure the string is
    // null terminated.
    DWORD cchData = cbData / sizeof(WCHAR) + 1;
    hr = StrAlloc(ppwzCustomActionData, cchData);
    ExitOnFailure(hr, "Failed to copy ca script.");

    CopyMemory(*ppwzCustomActionData, pbData, cbData);
    (*ppwzCustomActionData)[cchData - 1] = L'\0';

LExit:
    ReleaseMem(pbData);
    return hr;
}