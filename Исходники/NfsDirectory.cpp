bool CNfsDirectory::GetResource(const CURI& path, CFileItem &item)
{
  if(path.GetProtocol() != "nfs")
  {
     CLog::Log(LOGERROR, "CNfsDirectory::%s - invalid protocol [%s]", __func__, path.GetProtocol().c_str());
     return false;
  }

  CStdString strHostName = path.GetHostName();
  CStdString strFullPath = path.GetFileName();
  CStdString strFileName, strExportDir;

  int iPos = strFullPath.Find(":", 0);
  if (iPos != -1)
  {
    strExportDir = strFullPath.substr(0, iPos);
    strFileName  = strFullPath.substr(iPos + 1, strFullPath.length());
  }
  else
  {
    strExportDir = strFullPath;
  }

  CStdString strMountPoint = GetMountPoint("nfs",  strHostName, strExportDir);

  // path is not mounted - need to mount it
  if(!CUtil::IsMountpoint(strMountPoint) && CUtil::GetFsMagic(strMountPoint+strFileName) != NFS_SUPER_MAGIC)
  {
    CStdString nfsPath = strHostName + ":" + "/" + strExportDir;

    CLog::Log(LOGDEBUG, "CNfsDirectory::%s - mounting NFS share [%s] ==> [%s]", __func__, nfsPath.c_str(), strMountPoint.c_str());

    if(MountShare(nfsPath, strMountPoint) == false)
    {
      CLog::Log(LOGERROR, "CNfsDirectory::%s - failed to mount NFS share [%s]", __func__, nfsPath.c_str());
      return false;
    }
  }

  CStdString strHddPath = strMountPoint + strFileName;

  item.m_strPath = strHddPath;
  item.SetLabel(path.Get());

  item.SetProperty("filename", strFileName);
  item.SetProperty("mountpoint", strMountPoint);

  struct stat st;
  if (stat(strHddPath.c_str(),&st) == 0)
  {
    item.m_bIsFolder = S_ISDIR(st.st_mode);
  }

  return true;
}