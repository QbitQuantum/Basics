BOOLEAN KShieldDirectoryTree::Add(PWSTR pwszFullPath, PVOID pUserContext)
{
  KLocker locker(&m_KSynchroObject);

  if (pwszFullPath == NULL)
    return FALSE;

  int nPathLen = wcslen(pwszFullPath);
  int nSizeToken;
  PWSTR pwszFullPathSave = new WCHAR[nPathLen + sizeof(WCHAR)];
  if (pwszFullPathSave == NULL)
    return FALSE;
  wcscpy(pwszFullPathSave, pwszFullPath);
  PWSTR pwszEndPath = pwszFullPathSave + nPathLen;

  BOOLEAN bRes = FALSE;
  
  PWSTR pwszLast;
  //PWSTR pwszToken = _wcstok(pwszFullPathSave, L"\\/");
  PWSTR pwszToken = _wcstok(pwszFullPathSave, L"\\/", &pwszLast);

  if (pwszToken != NULL && m_pRoot == NULL)
  {
    m_pRoot = new KShieldDirectory(NULL);
    if (m_pRoot != NULL)
    {
      if (m_pRoot->Open(L"Root", NULL) != TRUE)
      {
        pwszToken = NULL;
        delete m_pRoot;
        m_pRoot = NULL;
      }
    }
    else
    {
      pwszToken = NULL;
    }
  }

  KShieldDirectory* pCurrentDir = m_pRoot;
  KShieldDirectory* pItem;
  PVOID pUserContextTmp;
  while (pwszToken != NULL)
  {
    pItem = pCurrentDir->Find(pwszToken);
    if (pItem == NULL)
    {
      pItem = pCurrentDir->Add(pwszToken, NULL);
      if (pItem == NULL)
        break;
    }
    nSizeToken = wcslen(pwszToken);
    if ((pwszToken+nSizeToken) != pwszEndPath)
      pUserContextTmp = NULL;
    else
      pUserContextTmp = pUserContext;

    if (pItem->m_pDirectoryInfo != NULL && pItem->m_pDirectoryInfo->m_pUserContext == NULL)
    {
      pItem->m_pDirectoryInfo->m_pUserContext = pUserContextTmp;
      if ((pwszToken+nSizeToken) == pwszEndPath)
      {
        if (pCurrentDir->m_pDirectoryInfo != NULL && pUserContextTmp != NULL)
          ++(pCurrentDir->m_pDirectoryInfo->m_dwUserCount);
        bRes = TRUE;
      }
    }

    pCurrentDir = pItem;

    pwszToken = _wcstok(NULL, L"\\/", &pwszLast);
  }

  delete[] pwszFullPathSave;

  return bRes;
}