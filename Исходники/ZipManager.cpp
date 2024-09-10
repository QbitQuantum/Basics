bool CZipManager::GetZipEntry(const CURL& url, SZipEntry& item)
{
  std::string strFile = url.GetHostName();

  map<std::string,vector<SZipEntry> >::iterator it = mZipMap.find(strFile);
  vector<SZipEntry> items;
  if (it == mZipMap.end()) // we need to list the zip
  {
    GetZipList(url,items);
  }
  else
  {
    items = it->second;
  }

  std::string strFileName = url.GetFileName();
  for (vector<SZipEntry>::iterator it2=items.begin();it2 != items.end();++it2)
  {
    if (std::string(it2->name) == strFileName)
    {
      memcpy(&item,&(*it2),sizeof(SZipEntry));
      return true;
    }
  }
  return false;
}