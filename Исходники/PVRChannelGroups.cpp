CFileItemPtr CPVRChannelGroups::GetByPath(const CStdString &strPath) const
{
  // get the filename from curl
  CURL url(strPath);
  CStdString strFileName = url.GetFileName();
  URIUtils::RemoveSlashAtEnd(strFileName);

  CStdString strCheckPath;
  for (std::vector<CPVRChannelGroupPtr>::const_iterator it = m_groups.begin(); it != m_groups.end(); it++)
  {
    // check if the path matches
    strCheckPath.Format("channels/%s/%s/", (*it)->IsRadio() ? "radio" : "tv", (*it)->GroupName().c_str());
    if (strFileName.Left(strCheckPath.length()) == strCheckPath)
    {
      strFileName.erase(0, strCheckPath.length());
      return (*it)->GetByIndex(atoi(strFileName.c_str()));
    }
  }

  // no match
  CFileItemPtr retVal(new CFileItem);
  return retVal;
}