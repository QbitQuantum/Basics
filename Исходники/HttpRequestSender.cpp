BOOL CHttpRequestSender::WriteTextPart(HINTERNET hRequest, CString sName)
{
  BOOL bRet = FALSE;
    
  /* Write part header */
  CString sHeader;
  bRet= FormatTextPartHeader(sName, sHeader);
  if(!bRet)
  {
    m_Assync->SetProgress(_T("Error formatting text part header."), 0);
    return FALSE;
  }
  
  strconv_t strconv;
  LPCSTR pszHeader = strconv.t2a(sHeader);
  if(pszHeader==NULL)
  {
    m_Assync->SetProgress(_T("Error converting text part header to ASCII."), 0);
    return FALSE;
  }

  DWORD dwBytesWritten = 0;
  bRet=InternetWriteFile(hRequest, pszHeader, (DWORD)strlen(pszHeader), &dwBytesWritten);
	if(!bRet)
  {
    m_Assync->SetProgress(_T("Error uploading text part header."), 0);
    return FALSE;
  }
  UploadProgress(dwBytesWritten);

  /* Write form data */

  std::map<CString, std::string>::iterator it = m_Request.m_aTextFields.find(sName);
  if(it==m_Request.m_aTextFields.end())
  {
    m_Assync->SetProgress(_T("Error searching for text part header name."), 0);
    return FALSE; 
  }
  
  size_t nDataSize = it->second.length();
  int pos = 0;    
  DWORD dwBytesRead = 0;
  for(;;)
  {
    if(m_Assync->IsCancelled())
    {
      return FALSE;
    }

    dwBytesRead = (DWORD)MIN(1024, nDataSize-pos);    
    if(dwBytesRead==0)
      break; // EOF

    std::string sBuffer = it->second.substr(pos, dwBytesRead);
    
    DWORD dwBytesWritten = 0;
    bRet=InternetWriteFile(hRequest, sBuffer.c_str(), dwBytesRead, &dwBytesWritten);
	  if(!bRet)
    {
      m_Assync->SetProgress(_T("Error uploading text part data."), 0);
      return FALSE;
    }
    UploadProgress(dwBytesWritten);

    pos += dwBytesRead;    
  }

  /* Write part footer */

  CString sFooter;
  bRet= FormatTextPartFooter(sName, sFooter);
  if(!bRet)
  {
    m_Assync->SetProgress(_T("Error formatting text part footer."), 0);
    return FALSE;
  }
  
  LPCSTR pszFooter = strconv.t2a(sFooter);
  if(pszFooter==NULL)
  {
    m_Assync->SetProgress(_T("Error converting text part footer to ASCII."), 0);
    return FALSE;
  }

  bRet=InternetWriteFile(hRequest, pszFooter, (DWORD)strlen(pszFooter), &dwBytesWritten);
	if(!bRet)
  {
    m_Assync->SetProgress(_T("Error uploading text part footer."), 0);
    return FALSE;
  }
  UploadProgress(dwBytesWritten);

  return TRUE;
}