//
// RunRegKeys
//
void StartupRunner::_RunRegKeys(HKEY hkParent, LPCTSTR ptzSubKey, DWORD dwFlags)
{
#ifdef _WIN64
    if (dwFlags & ERK_WIN64_BOTH)
#else
    if (IsOS(OS_WOW6432) && (dwFlags & ERK_WIN64_BOTH))
#endif
    {
        dwFlags &= ~ERK_WIN64_BOTH;
        _RunRegKeysWorker(hkParent, ptzSubKey, dwFlags | ERK_WIN64_KEY64);
        _RunRegKeysWorker(hkParent, ptzSubKey, dwFlags | ERK_WIN64_KEY32);
    }
    else
    {
        _RunRegKeysWorker(hkParent, ptzSubKey, dwFlags);
    }
}