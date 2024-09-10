DWORD CopyWideString(
    IN _In_ LPWSTR pSrcWString,
    OUT _Out_ LPWSTR *pDestWString)
{
    DWORD retCode = NO_ERROR;
    HRESULT hr = S_OK;
    size_t dwStringLength = 0;
    LPWSTR pTempString = NULL;

    *pDestWString = NULL;

    // Nothing to copy
    if(!pSrcWString)
        goto Cleanup;

    hr = StringCbLengthW(pSrcWString, (size_t)(STRSAFE_MAX_CCH * sizeof(wchar_t)), &dwStringLength);
    if (FAILED(hr))
    {
        retCode = HRESULT_CODE(hr);
        goto Cleanup;
    }

    // StringCbLengthW - returns the length of string in bytes (excluding the null character).
    // StringCbCopyW expects the length of string in bytes (including the null character).
    dwStringLength += sizeof(wchar_t);
    retCode = AllocateMemory((DWORD)dwStringLength, (PVOID *)&pTempString);
    if(retCode != NO_ERROR)
    {
        goto Cleanup;
    }

    hr = StringCbCopyW((LPTSTR)pTempString, dwStringLength, pSrcWString);
    if (FAILED(hr))
    {
        retCode = HRESULT_CODE(hr);
        goto Cleanup;
    }

    //
    // Set the OUT parameter
    //
    *pDestWString = pTempString;

Cleanup:
    if((retCode != NO_ERROR) && (pTempString != NULL))
        FreeMemory((PVOID *)&pTempString);
    pTempString = NULL;
    return retCode;
}