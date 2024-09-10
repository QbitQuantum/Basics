bool CNfsConnection::Connect(const CURL& url, CStdString &relativePath)
{
  CSingleLock lock(*this);
  bool ret = false;
  int nfsRet = 0;
  CStdString exportPath = "";

  resolveHost(url);
  ret = splitUrlIntoExportAndPath(url, exportPath, relativePath);
  
  if( (ret && (!exportPath.Equals(m_exportPath,true)  || 
      !url.GetHostName().Equals(m_hostName,false)))    ||
      (XbmcThreads::SystemClockMillis() - m_lastAccessedTime) > CONTEXT_TIMEOUT )
  {
    int contextRet = getContextForExport(url.GetHostName() + exportPath);
    
    if(contextRet == CONTEXT_INVALID)//we need a new context because sharename or hostname has changed
    {
      return false;
    }
    
    if(contextRet == CONTEXT_NEW) //new context was created - we need to mount it
    {
      //we connect to the directory of the path. This will be the "root" path of this connection then.
      //So all fileoperations are relative to this mountpoint...
      nfsRet = m_pLibNfs->nfs_mount(m_pNfsContext, m_resolvedHostName.c_str(), exportPath.c_str());

      if(nfsRet != 0) 
      {
        CLog::Log(LOGERROR,"NFS: Failed to mount nfs share: %s (%s)\n", exportPath.c_str(), m_pLibNfs->nfs_get_error(m_pNfsContext));
        destroyContext(url.GetHostName() + exportPath);
        return false;
      }
      CLog::Log(LOGDEBUG,"NFS: Connected to server %s and export %s\n", url.GetHostName().c_str(), exportPath.c_str());
    }
    m_exportPath = exportPath;
    m_hostName = url.GetHostName();
    //read chunksize only works after mount
    m_readChunkSize = m_pLibNfs->nfs_get_readmax(m_pNfsContext);
    m_writeChunkSize = m_pLibNfs->nfs_get_writemax(m_pNfsContext);

    if(contextRet == CONTEXT_NEW)
    {
      CLog::Log(LOGDEBUG,"NFS: chunks: r/w %i/%i\n", (int)m_readChunkSize,(int)m_writeChunkSize);          
    }
  }
  return ret; 
}