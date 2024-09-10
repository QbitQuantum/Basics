BOOL COXQuickString::SetString(LPCTSTR szText, int nCount)
{
    // We do a fresh memory allocation when setting the string.
    Empty();

    if (!szText || nCount <= 0)
        return TRUE;

    m_nLength = min(PtrToUint(_tcslen(szText)), (UINT)nCount);
    m_nBufferSize = m_nLength + 1;

    m_szText = AllocBuffer(m_nBufferSize);
    if (!m_szText)
        return FALSE;

	UTBStr::tcsncpy(m_szText, m_nBufferSize, szText, m_nLength+1);
    m_szText[m_nLength] = TEXT('\0');

    return TRUE;
}