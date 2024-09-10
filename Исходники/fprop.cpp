static UINT
LoadPropSheetHandlers(LPCWSTR pwszPath, PROPSHEETHEADERW *pHeader, UINT cMaxPages, HPSXA *phpsxa, IDataObject *pDataObj)
{
    WCHAR wszBuf[MAX_PATH];
    UINT cPages = 0, i = 0;

    LPWSTR pwszFilename = PathFindFileNameW(pwszPath);
    BOOL bDir = PathIsDirectoryW(pwszPath);

    if (bDir)
    {
        phpsxa[i] = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, L"Folder", cMaxPages - cPages, pDataObj);
        cPages += SHAddFromPropSheetExtArray(phpsxa[i++], AddPropSheetPageCallback, (LPARAM)pHeader);

        phpsxa[i] = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, L"Directory", cMaxPages - cPages, pDataObj);
        cPages += SHAddFromPropSheetExtArray(phpsxa[i++], AddPropSheetPageCallback, (LPARAM)pHeader);
    }
    else
    {
        /* Load property sheet handlers from ext key */
        LPWSTR pwszExt = PathFindExtensionW(pwszFilename);
        phpsxa[i] = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, pwszExt, cMaxPages - cPages, pDataObj);
        cPages += SHAddFromPropSheetExtArray(phpsxa[i++], AddPropSheetPageCallback, (LPARAM)pHeader);

        /* Load property sheet handlers from prog id key */
        DWORD cbBuf = sizeof(wszBuf);
        if (RegGetValueW(HKEY_CLASSES_ROOT, pwszExt, L"", RRF_RT_REG_SZ, NULL, wszBuf, &cbBuf) == ERROR_SUCCESS)
        {
            TRACE("EnumPropSheetExt wszBuf %s, pwszExt %s\n", debugstr_w(wszBuf), debugstr_w(pwszExt));
            phpsxa[i] = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, wszBuf, cMaxPages - cPages, pDataObj);
            cPages += SHAddFromPropSheetExtArray(phpsxa[i++], AddPropSheetPageCallback, (LPARAM)pHeader);
        }

        /* Add property sheet handlers from "*" key */
        phpsxa[i] = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, L"*", cMaxPages - cPages, pDataObj);
        cPages += SHAddFromPropSheetExtArray(phpsxa[i++], AddPropSheetPageCallback, (LPARAM)pHeader);
    }

    return cPages;
}