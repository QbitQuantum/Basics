BOOL CNTServiceControlManager::Unlock()
{
  BOOL bSuccess = TRUE;
  if (m_hLock)
  {
    bSuccess = UnlockServiceDatabase(m_hLock);
    m_hLock = NULL;
  }

  return bSuccess;
}