NS_IMETHODIMP nsPop3IncomingServer::MarkMessages()
{
  nsresult rv;
  if (m_runningProtocol)
    rv = m_runningProtocol->MarkMessages(&m_uidlsToMark);
  else
  {
    nsCString hostName;
    nsCString userName;
    nsCOMPtr<nsIFile> localPath;

    GetLocalPath(getter_AddRefs(localPath));

    GetHostName(hostName);
    GetUsername(userName);
    // do it all in one fell swoop
    rv = nsPop3Protocol::MarkMsgForHost(hostName.get(), userName.get(), localPath, m_uidlsToMark);
  }
  uint32_t count = m_uidlsToMark.Length();
  for (uint32_t i = 0; i < count; i++)
  {
    Pop3UidlEntry *ue = m_uidlsToMark[i];
    PR_Free(ue->uidl);
    PR_Free(ue);
  }
  m_uidlsToMark.Clear();
  return rv;
}