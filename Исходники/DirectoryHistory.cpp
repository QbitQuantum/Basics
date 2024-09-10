const CStdString& CDirectoryHistory::GetSelectedItem(const CStdString& strDirectory) const
{
  CStdString strDir = strDirectory;
  strDir.ToLower();
  while (CUtil::HasSlashAtEnd(strDir) )
  {
    strDir = strDir.Left(strDir.size() - 1);
  }
  for (int i = 0; i < (int)m_vecHistory.size(); ++i)
  {
    const CHistoryItem& item = m_vecHistory[i];
    if ( strDir == item.m_strDirectory)
    {

      return item.m_strItem;
    }
  }
  return m_strNull;
}