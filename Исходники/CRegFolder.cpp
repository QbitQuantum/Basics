HRESULT CGuidItemContextMenu_CreateInstance(PCIDLIST_ABSOLUTE pidlFolder,
                                            HWND hwnd,
                                            UINT cidl,
                                            PCUITEMID_CHILD_ARRAY apidl,
                                            IShellFolder *psf,
                                            IContextMenu **ppcm)
{
    HKEY hKeys[10];
    UINT cKeys = 0;

    GUID *pGuid = _ILGetGUIDPointer(apidl[0]);
    if (pGuid)
    {
        LPOLESTR pwszCLSID;
        WCHAR key[60];

        wcscpy(key, L"CLSID\\");
        HRESULT hr = StringFromCLSID(*pGuid, &pwszCLSID);
        if (hr == S_OK)
        {
            wcscpy(&key[6], pwszCLSID);
            AddClassKeyToArray(key, hKeys, &cKeys);
        }
    }
    AddClassKeyToArray(L"Folder", hKeys, &cKeys);

    return CDefFolderMenu_Create2(pidlFolder, hwnd, cidl, apidl, psf, RegFolderContextMenuCallback, cKeys, hKeys, ppcm);
}