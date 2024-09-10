UniqueApp::UniqueApp() : m_hMutex(NULL)
{
  strcpy(m_szKey, LOCAL_PREFIX);
  size_t uPrefixLen = strlen(LOCAL_PREFIX);
  char* szExecPath = m_szKey + uPrefixLen;
  GetModuleFileNameA(NULL, szExecPath, sizeof(m_szKey) - uPrefixLen);
  char* pChar = szExecPath;
  while (*pChar)
  {
    if (*pChar == '\\')
      *pChar = '/';
    pChar++;
  }
  CharLowerBuffA(szExecPath, strlen(szExecPath));
}