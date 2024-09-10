HRESULT CDrivesContextMenu_CreateInstance(PCIDLIST_ABSOLUTE pidlFolder,
                                          HWND hwnd,
                                          UINT cidl,
                                          PCUITEMID_CHILD_ARRAY apidl,
                                          IShellFolder *psf,
                                          IContextMenu **ppcm)
{
    HKEY hKeys[2];
    UINT cKeys = 0;
    AddClassKeyToArray(L"Drive", hKeys, &cKeys);
    AddClassKeyToArray(L"Folder", hKeys, &cKeys);

    return CDefFolderMenu_Create2(pidlFolder, hwnd, cidl, apidl, psf, DrivesContextMenuCallback, cKeys, hKeys, ppcm);
}