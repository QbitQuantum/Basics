BOOL KProcessInfo::IsSpecialProc()
{
    LPCWSTR pwcszPath = NULL;
    LPWSTR  pwszFileName = NULL;

    if (!m_bFirstCheck)
    {
        return m_bSpecialProc;
    }

    m_bFirstCheck = FALSE;

    pwcszPath = GetProcPath();
    if (NULL == pwcszPath)
    {
        return FALSE;
    }
    
    pwszFileName = PathFindFileNameW(pwcszPath);
    if (NULL == pwszFileName)
    {
        return FALSE;
    }

    if (wcsicmp(pwszFileName, L"wscript.exe") == 0 ||
        wcsicmp(pwszFileName, L"rundll32.exe") == 0)
    {
        m_bSpecialProc = TRUE;
        return TRUE;
    }

    return FALSE;
}