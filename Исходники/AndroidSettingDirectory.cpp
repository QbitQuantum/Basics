bool CAndroidSettingDirectory::GetDirectory(const CURL& url, CFileItemList &items)
{
  std::string dirname = url.GetFileName();
  URIUtils::RemoveSlashAtEnd(dirname);
  int sdk = CJNIBase::GetSDKVersion();
  CLog::Log(LOGDEBUG, "CAndroidSettingDirectory::GetDirectory: %s (sdk:%d;intents:%d)",dirname.c_str(), sdk, m_intents.size());
  if (dirname == "settings")
  {
    for(size_t i=0; i < m_intents.size(); ++i)
    {
      int sdk = CJNIBase::GetSDKVersion();
      if (m_intents[i].sdk > sdk)
        continue;

      CFileItemPtr pItem(new CFileItem(m_intents[i].intent));
      pItem->m_bIsFolder = false;
      std::string path = StringUtils::Format("androidsetting://%s/%s/%s", url.GetHostName().c_str(), dirname.c_str(), m_intents[i].intent.c_str());
      pItem->SetPath(path);
      pItem->SetLabel(m_intents[i].name);
      pItem->SetArt("thumb", "DefaultProgram.png");
      items.Add(pItem);
    }
    return true;
  }

  CLog::Log(LOGERROR, "CAndroidSettingDirectory::GetDirectory Failed to open %s",url.Get().c_str());
  return false;
}