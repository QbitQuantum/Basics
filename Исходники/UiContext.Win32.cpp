static std::wstring SHGetPathFromIDListLongPath(LPCITEMIDLIST pidl)
{
    std::wstring pszPath(MAX_PATH, 0);
    while (!SHGetPathFromIDListEx(pidl, &pszPath[0], (DWORD)pszPath.size(), 0))
    {
        if (pszPath.size() >= SHRT_MAX)
        {
            // Clearly not succeeding at all, bail
            return std::wstring();
        }
        pszPath.resize(pszPath.size() * 2);
    }
    return pszPath;
}