HRESULT WINAPI CExeDropHandler::Drop(IDataObject *pDataObject, DWORD dwKeyState, POINTL pt, DWORD *pdwEffect)
{
    TRACE ("(%p)\n", this);    
    FORMATETC fmt;
    STGMEDIUM medium;
    LPWSTR pszSrcList;
    InitFormatEtc (fmt, CF_HDROP, TYMED_HGLOBAL);
    WCHAR wszBuf[MAX_PATH * 2 + 8], *pszEnd = wszBuf;
    size_t cchRemaining = _countof(wszBuf);

    if (SUCCEEDED(pDataObject->GetData(&fmt, &medium)) /* && SUCCEEDED(pDataObject->GetData(&fmt2, &medium))*/)
    {
        LPDROPFILES lpdf = (LPDROPFILES) GlobalLock(medium.hGlobal);
        if (!lpdf)
        {
            ERR("Error locking global\n");
            return E_FAIL;
        }
        pszSrcList = (LPWSTR) (((byte*) lpdf) + lpdf->pFiles);
        while (*pszSrcList)
        {
            if (StrChrW(pszSrcList, L' ') && cchRemaining > 3)
                StringCchPrintfExW(pszEnd, cchRemaining, &pszEnd, &cchRemaining, 0, L"\"%ls\" ", pszSrcList);
            else
                StringCchPrintfExW(pszEnd, cchRemaining, &pszEnd, &cchRemaining, 0, L"%ls ", pszSrcList);
            
            pszSrcList += wcslen(pszSrcList) + 1;
        }
    }

    ShellExecuteW(NULL, L"open", sPathTarget, wszBuf, NULL,SW_SHOWNORMAL);

    return S_OK;
}