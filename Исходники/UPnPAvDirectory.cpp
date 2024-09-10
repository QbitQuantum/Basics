bool
CUPnPAvDirectory::GetResource(const CURI& path, CFileItem &item)
{
  CStdString strFileName = path.GetFileName();
  CStdString strHostName = path.GetHostName();
  CStdString strHddPath;

  CUtil::UrlDecode(strHostName);

  strHddPath.Format("%s/%s/%s", UPNP_MNT, strHostName, strFileName);

  if(!CFile::Exists(strHddPath))
  {
    CLog::Log(LOGERROR, "CUPnPAvDirectory::%s - upnp node [%s] for [%s] doesnt exists", __func__, strHddPath.c_str(), path.Get().c_str());
    return false;
  }

  item.m_strPath = strHddPath;
  item.SetLabel(path.Get());

  struct stat st;
  if (stat(strHddPath.c_str(),&st) == 0)
  {
    item.m_bIsFolder = S_ISDIR(st.st_mode);
  }

  return true;
}