BOOL INSTAPI
SQLSetKeywordValueW (LPCWSTR lpszSection,
    LPCWSTR lpszEntry, LPWSTR lpszString, int cbString)
{
  return SQLWritePrivateProfileStringW (lpszSection,
      lpszEntry, lpszString, L"odbc.ini");
}