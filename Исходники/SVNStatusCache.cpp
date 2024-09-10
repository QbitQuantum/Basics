CString CSVNStatusCache::GetSpecialFolder(REFKNOWNFOLDERID rfid)
{
    PWSTR pszPath = NULL;
    if (SHGetKnownFolderPath(rfid, KF_FLAG_CREATE, NULL, &pszPath) != S_OK)
        return CString();

    CString path = pszPath;
    CoTaskMemFree(pszPath);
    return path;
}