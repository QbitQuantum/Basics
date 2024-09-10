//
// lpRedirectedKey is allocated and returned from this method.  Caller owns the new string and
// should release
//
HRESULT RedirectKey(REGSAM samDesired, HKEY hKey, LPCWSTR lpKey, __deref_out_z LPWSTR * lpRedirectedKey)
{
    if (hKey != kRegistryRootHive || _wcsnicmp(lpKey, kRegistryRootKey, wcslen(kRegistryRootKey)) != 0)
    {
        return ERROR_SUCCESS;
    }
    
    LPCWSTR lpRootStrippedKey = lpKey + wcslen(kRegistryRootKey);
    size_t redirectedLength = wcslen(g_registryRoot) + wcslen(lpRootStrippedKey) + 1;
    
    bool bUseWow = false;
    HRESULT hr = CheckUseWow6432Node(samDesired, &bUseWow);
    
    if (hr != ERROR_SUCCESS)
    {
        return hr;
    }
    
    if (bUseWow)
    {
        redirectedLength += wcslen(kWow6432Node);
    }
    
    *lpRedirectedKey = new (nothrow) WCHAR[redirectedLength];
    
    if (*lpRedirectedKey == NULL)
    {
        return ERROR_NOT_ENOUGH_MEMORY;
    }
    
    wcscpy_s(*lpRedirectedKey, redirectedLength, g_registryRoot);
    if (bUseWow)
    {
        StringCchCat(*lpRedirectedKey, redirectedLength, kWow6432Node);
    }
    
    StringCchCat(*lpRedirectedKey, redirectedLength, lpRootStrippedKey);
    
    return ERROR_SUCCESS;
}