bool Cx_CfgRecord::SetDate(const wchar_t* pszEntry, int year, int month, int day)
{
    wchar_t szBuf[60];
    swprintf_s(szBuf, _countof(szBuf), L"'%d-%d-%d'", year, month, day);
    return AddFieldValue(pszEntry, szBuf);
}