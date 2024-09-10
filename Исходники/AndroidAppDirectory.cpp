bool CAndroidAppDirectory::GetDirectory(const CURL& url, CFileItemList &items)
{
  std::string dirname = url.GetFileName();
  URIUtils::RemoveSlashAtEnd(dirname);
  CLog::Log(LOGDEBUG, "CAndroidAppDirectory::GetDirectory: %s",dirname.c_str()); 
  if (dirname == "apps")
  {
    vector<androidPackage> applications;
    CXBMCApp::ListApplications(&applications);
    if (!applications.size())
    {
      CLog::Log(LOGERROR, "CAndroidAppDirectory::GetDirectory Application lookup listing failed");
      return false;
    }
    for(unsigned int i = 0; i < applications.size(); i++)
    {
      if (applications[i].packageName == "org.xbmc.xbmc")
        continue;
      CFileItemPtr pItem(new CFileItem(applications[i].packageName));
      pItem->m_bIsFolder = false;
      std::string path = StringUtils::Format("androidapp://%s/%s/%s", url.GetHostName().c_str(), dirname.c_str(),  applications[i].packageName.c_str());
      pItem->SetPath(path);
      pItem->SetLabel(applications[i].packageLabel);
      pItem->SetArt("thumb", path+".png");
      items.Add(pItem);
    }
    return true;
  }

  CLog::Log(LOGERROR, "CAndroidAppDirectory::GetDirectory Failed to open %s", url.Get().c_str());
  return false;
}