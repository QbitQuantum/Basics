// This method compresses the files contained in the report and produces ZIP archive.
BOOL CErrorReportSender::CompressReportFiles()
{ 
  BOOL bStatus = FALSE;
  strconv_t strconv;
  zipFile hZip = NULL;
  CString sMsg;
  LONG64 lTotalSize = 0;
  LONG64 lTotalCompressed = 0;
  BYTE buff[1024];
  DWORD dwBytesRead=0;
  HANDLE hFile = INVALID_HANDLE_VALUE;
  std::map<CString, FileItem>::iterator it;
  LARGE_INTEGER lFileSize;
  BOOL bGetSize = FALSE;
    
  if(m_bExport)
    m_Assync.SetProgress(_T("[exporting_report]"), 0, false);
  else
    m_Assync.SetProgress(_T("[compressing_files]"), 0, false);

  m_Assync.SetProgress(_T("Calculating total size of files to compress..."), 0, false);
  
  for(it=g_CrashInfo.m_FileItems.begin(); it!=g_CrashInfo.m_FileItems.end(); it++)
  {    
    if(m_Assync.IsCancelled())    
      goto cleanup;

    CString sFileName = it->second.m_sSrcFile.GetBuffer(0);
    hFile = CreateFile(sFileName, 
      GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
    if(hFile==INVALID_HANDLE_VALUE)
    {
      sMsg.Format(_T("Couldn't open file %s"), sFileName);
      m_Assync.SetProgress(sMsg, 0, false);
      continue;
    }
    
    bGetSize = GetFileSizeEx(hFile, &lFileSize);
    if(!bGetSize)
    {
      sMsg.Format(_T("Couldn't get file size of %s"), sFileName);
      m_Assync.SetProgress(sMsg, 0, false);
      CloseHandle(hFile);
      continue;
    }

    lTotalSize += lFileSize.QuadPart;
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
  }

  sMsg.Format(_T("Total file size for compression is %I64d"), lTotalSize);
  m_Assync.SetProgress(sMsg, 0, false);

  if(m_bExport)
    m_sZipName = m_sExportFileName;  
  else
    m_sZipName = g_CrashInfo.m_sErrorReportDirName + _T(".zip");  
    
  sMsg.Format(_T("Creating ZIP archive file %s"), m_sZipName);
  m_Assync.SetProgress(sMsg, 1, false);

  hZip = zipOpen(strconv.t2a(m_sZipName.GetBuffer(0)), APPEND_STATUS_CREATE);
  if(hZip==NULL)
  {
    m_Assync.SetProgress(_T("Failed to create ZIP file."), 100, true);
    goto cleanup;
  }

  for(it=g_CrashInfo.m_FileItems.begin(); it!=g_CrashInfo.m_FileItems.end(); it++)
  { 
    if(m_Assync.IsCancelled())    
      goto cleanup;
    
    CString sDstFileName = it->second.m_sDestFile.GetBuffer(0);
    CString sFileName = it->second.m_sSrcFile.GetBuffer(0);
    CString sDesc = it->second.m_sDesc;

    sMsg.Format(_T("Compressing %s"), sDstFileName);
    m_Assync.SetProgress(sMsg, 0, false);
        
    HANDLE hFile = CreateFile(sFileName, 
      GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
    if(hFile==INVALID_HANDLE_VALUE)
    {
      sMsg.Format(_T("Couldn't open file %s"), sFileName);
      m_Assync.SetProgress(sMsg, 0, false);
      continue;
    }

    BY_HANDLE_FILE_INFORMATION fi;
    GetFileInformationByHandle(hFile, &fi);

    SYSTEMTIME st;
    FileTimeToSystemTime(&fi.ftCreationTime, &st);

    zip_fileinfo info;
    info.dosDate = 0;
    info.tmz_date.tm_year = st.wYear;
    info.tmz_date.tm_mon = st.wMonth;
    info.tmz_date.tm_mday = st.wDay;
    info.tmz_date.tm_hour = st.wHour;
    info.tmz_date.tm_min = st.wMinute;
    info.tmz_date.tm_sec = st.wSecond;
    info.external_fa = FILE_ATTRIBUTE_NORMAL;
    info.internal_fa = FILE_ATTRIBUTE_NORMAL;

    int n = zipOpenNewFileInZip( hZip, strconv.t2a(sDstFileName), &info,
              NULL, 0, NULL, 0, strconv.t2a(sDesc), Z_DEFLATED, Z_DEFAULT_COMPRESSION);
    if(n!=0)
    {
      sMsg.Format(_T("Couldn't compress file %s"), sDstFileName);
      m_Assync.SetProgress(sMsg, 0, false);
      continue;
    }

    for(;;)
    {
      if(m_Assync.IsCancelled())    
        goto cleanup;

      BOOL bRead = ReadFile(hFile, buff, 1024, &dwBytesRead, NULL);
      if(!bRead || dwBytesRead==0)
        break;

      int res = zipWriteInFileInZip(hZip, buff, dwBytesRead);
      if(res!=0)
      {
        zipCloseFileInZip(hZip);
        sMsg.Format(_T("Couldn't write to compressed file %s"), sDstFileName);
        m_Assync.SetProgress(sMsg, 0, false);        
        break;
      }

      lTotalCompressed += dwBytesRead;

      float fProgress = 100.0f*lTotalCompressed/lTotalSize;
      m_Assync.SetProgress((int)fProgress, false);
    }

    zipCloseFileInZip(hZip);
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
  }

  if(lTotalSize==lTotalCompressed)
    bStatus = TRUE;

cleanup:

  if(hZip!=NULL)
    zipClose(hZip, NULL);

  if(hFile!=INVALID_HANDLE_VALUE)
    CloseHandle(hFile);

  if(bStatus)
    m_Assync.SetProgress(_T("Finished compressing files...OK"), 100, true);
  else
    m_Assync.SetProgress(_T("File compression failed."), 100, true);

  if(m_bExport)
  {
    if(bStatus)
      m_Assync.SetProgress(_T("[end_exporting_report_ok]"), 100, false);    
    else
      m_Assync.SetProgress(_T("[end_exporting_report_failed]"), 100, false);    
  }
  else
  {    
    m_Assync.SetProgress(_T("[end_compressing_files]"), 100, false);   
  }

  return bStatus;
}