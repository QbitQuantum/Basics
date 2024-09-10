BOOL FileUpload(Zimbra::Rpc::ZimbraConnection *z_connection, LPWSTR *ppwszToken)
{
    LOGFN_INTERNAL_NO;

    LPSTR pszTestFile = "E:\\temp\\aa.log";
    LPSTREAM pStreamFile = NULL;
    HRESULT hr = OpenStreamOnFile(MAPIAllocateBuffer, MAPIFreeBuffer, STGM_READ,
        (LPWSTR)pszTestFile, NULL, &pStreamFile);

    if (FAILED(hr))
    {
        LOG_ERROR(_T("failed to OpenStreamOnFile call: %x"), hr);
        return FALSE;
    }

    HANDLE hFile = CreateFile(L"E:\\temp\\aa.log", GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD dwFileSize = GetFileSize(hFile, NULL);

    CloseHandle(hFile);
    _tprintf(_T("  File Upload size=%d bytes\n"), dwFileSize);

    BOOL bResult = z_connection->DoFileUpload(pStreamFile, dwFileSize,
        L"/service/upload?fmt=raw", ppwszToken, NULL);

    pStreamFile->Release();

    return bResult;
}