BOOL CHttpSender::_Send(CString sURL, CString sFileName, AssyncNotification* an)
{ 
  BOOL bStatus = FALSE;
	TCHAR* hdrs = _T("Content-Type: application/x-www-form-urlencoded");
	LPCTSTR accept[2]={_T("*/*"), NULL};
  int uFileSize = 0;
  BYTE* uchFileData = NULL;
  HINTERNET hSession = NULL;
  HINTERNET hConnect = NULL;
  HINTERNET hRequest = NULL;
  TCHAR szProtocol[512];
  TCHAR szServer[512];
  TCHAR szURI[1024];
  DWORD dwPort;
  struct _stat st;
  int res = -1;
  FILE* f = NULL;
  BOOL bResult = FALSE;
  char* chPOSTRequest = NULL;
  CStringA sMD5Hash;
  CStringA sPOSTRequest;
  char* szPrefix="crashrpt=\"";
  char* szSuffix="\"";
  CString sErrorMsg;
  CHAR szResponce[1024];
  DWORD dwBufSize = 1024;
  MD5 md5;
  MD5_CTX md5_ctx;
  unsigned char md5_hash[16];
  int i=0;  
  CString msg;

  an->SetProgress(_T("Start sending error report over HTTP"), 0, false);

  an->SetProgress(_T("Creating Internet connection"), 3, false);

  if(an->IsCancelled()){ goto exit; }

  // Create Internet session
	hSession = InternetOpen(_T("CrashRpt"),
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hSession==NULL)
  {
    an->SetProgress(_T("Error creating Internet conection"), 0);
	  goto exit; // Couldn't create internet session
  }
  
  ParseURL(sURL, szProtocol, 512, szServer, 512, dwPort, szURI, 1024);

  an->SetProgress(_T("Connecting to server"), 5, false);

  // Connect to server
	hConnect = InternetConnect(
    hSession, 
    szServer,
		INTERNET_DEFAULT_HTTP_PORT, 
    NULL, 
    NULL, 
    INTERNET_SERVICE_HTTP, 
    0, 
    1);
	
	if(hConnect==NULL)
  {
    an->SetProgress(_T("Error connecting to server"), 0);
	  goto exit; // Couldn't connect
  }
	
  if(an->IsCancelled()){ goto exit; }

  an->SetProgress(_T("Preparing HTTP request data"), 7, false);

  // Load file data into memory
  res = _tstat(sFileName.GetBuffer(0), &st);
  if(res!=0)
  {
    an->SetProgress(_T("Error opening file"), 0);
    goto exit; // File not found
  }
  
  uFileSize = st.st_size;
  uchFileData = new BYTE[uFileSize];
#if _MSC_VER<1400
  f = _tfopen(sFileName.GetBuffer(0), _T("rb"));
#else
  _tfopen_s(&f, sFileName.GetBuffer(0), _T("rb"));
#endif
  if(!f || fread(uchFileData, uFileSize, 1, f)!=1)
  {
    an->SetProgress(_T("Error reading file"), 0);
    goto exit;  
  }
  fclose(f);

  md5.MD5Init(&md5_ctx);
  md5.MD5Update(&md5_ctx, uchFileData, uFileSize);
  md5.MD5Final(md5_hash, &md5_ctx);
  
  sMD5Hash = _T("&md5=");
  for(i=0; i<16; i++)
  {
    CString number;
    number.Format(_T("%02X"), md5_hash[i]);
    sMD5Hash += number;
  }
  
  sPOSTRequest = base64_encode(uchFileData, uFileSize).c_str();
  sPOSTRequest = szPrefix + sPOSTRequest + szSuffix;  
  sPOSTRequest.Replace("+", "%2B");
  sPOSTRequest.Replace("/", "%2F");  

  sPOSTRequest += sMD5Hash;
  
  an->SetProgress(_T("Opening HTTP request"), 10);

  if(an->IsCancelled()){ goto exit; }

  // Send POST request
  hRequest = HttpOpenRequest(hConnect, _T("POST"),
		                         szURI, NULL, NULL, accept, 0, 1);	
	if(hRequest==NULL)
  {
    an->SetProgress(_T("Error opening HTTP request"), 0);
	  goto exit; // Coudn't open request	
  }

  if(an->IsCancelled()){ goto exit; }

  an->SetProgress(_T("Sending HTTP request"), 50);
  bResult = HttpSendRequest(hRequest, hdrs, (int)_tcslen(hdrs), 
    (void*)sPOSTRequest.GetBuffer(), (DWORD)sPOSTRequest.GetLength());
    
  if(bResult == FALSE)
  {
    an->SetProgress(_T("Error sending HTTP request"), 100, false);
		goto exit; // Couldn't send request
  }
	  
  an->SetProgress(_T("Sending error report over HTTP completed OK"), 10, true);
    
  HttpQueryInfoA(hRequest, HTTP_QUERY_STATUS_CODE, szResponce, &dwBufSize, NULL); 
  if(atoi(szResponce)!=200)
  {
    CString msg;
    msg.Format(_T("Error! The server returned code %s"), CString(szResponce));
    an->SetProgress(msg, 0);
    goto exit;
  }    

  InternetReadFile(hRequest, szResponce, 1024, &dwBufSize);
  szResponce[dwBufSize] = 0;
  msg = CStringA(szResponce, dwBufSize);
  msg = _T("Server returned:")+msg;
  an->SetProgress(msg, 0);
    
  if(atoi(szResponce)!=200)
  {
    an->SetProgress(_T("Failed"), 100, false);
    goto exit;
  }

  an->SetProgress(_T("Sent OK"), 100, false);
  bStatus = TRUE;

exit:

  // Clean up
	if(hRequest) 
    InternetCloseHandle(hRequest);

	if(hConnect) 
    InternetCloseHandle(hConnect);

	if(hSession) 
    InternetCloseHandle(hSession);

  if(chPOSTRequest)
    delete [] chPOSTRequest;
    
  if(uchFileData)
    delete [] uchFileData;

  if(f)
    fclose(f);

  return bStatus;
}