XMLNode xmlLoadFromResource(const TCHAR* lpName,
                            LPCTSTR tag, 
                            XMLResults *pResults) {
  LPTSTR lpRes; 
  HRSRC hResInfo;
  HGLOBAL hRes; 
  int l, len;

  // Find the xml resource.
  hResInfo = FindResource (hInst, lpName, TEXT("XMLDialog")); 

  if (hResInfo == NULL) {
    MessageBoxX(hWndMainWindow,
      TEXT("Can't find resource"),
      TEXT("Dialog error"),
      MB_OK|MB_ICONEXCLAMATION);

    // unable to find the resource
    return XMLNode::emptyXMLNode;
  }

  // Load the wave resource. 
  hRes = LoadResource (hInst, hResInfo); 

  if (hRes == NULL) {
    MessageBoxX(hWndMainWindow,
      TEXT("Can't load resource"),
      TEXT("Dialog error"),
      MB_OK|MB_ICONEXCLAMATION);

    // unable to load the resource
    return XMLNode::emptyXMLNode;
  }

  // Lock the wave resource and do something with it. 
  lpRes = (LPTSTR)LockResource (hRes);
  
  if (lpRes) {
    l = SizeofResource(hInst,hResInfo);
    if (l>0) {
      char *buf= (char*)malloc(l+2);
      if (!buf) {
	//StartupStore(_T("------ LoadFromRes malloc error%s"),NEWLINE); // 100101
        MessageBoxX(hWndMainWindow,
                    TEXT("Can't allocate memory"),
                    TEXT("Dialog error"),
                    MB_OK|MB_ICONEXCLAMATION);
        // unable to allocate memory
        return XMLNode::emptyXMLNode;
      }
      strncpy(buf,(char*)lpRes,l);
      buf[l]=0; // need to explicitly null-terminate.
      buf[l+1]=0;
      len = l;      
      
#if defined(WIN32) || defined(UNDER_CE)
#ifdef _UNICODE
#if !defined(UNDER_CE) && (WINDOWSPC<1)
      if (!IsTextUnicode(buf,mmin(l,10000),NULL))
        {
#endif
          LPTSTR b2=(LPTSTR)malloc(l*2+2);
	  if (b2==NULL) StartupStore(_T(".... LoadFromRes Malloc1 failed\n")); // 100101
          MultiByteToWideChar(CP_ACP,          // code page
                              MB_PRECOMPOSED,  // character-type options
                              buf,             // string to map
                              l,               // number of bytes in string
                              b2,              // wide-character buffer
                              l*2+2);          // size of buffer
          free(buf);
          buf=(char*)b2;
          buf[l*2]= 0;
          buf[l*2+1]= 0;
#if !defined(UNDER_CE) && (WINDOWSPC<1)
        }
#endif
#else
      if (IsTextUnicode(buf,mmin(l,10000),NULL))
        {
          l>>=1;
          LPTSTR b2=(LPTSTR)malloc(l+2);
	  if (b2==NULL) StartupStore(_T(".... LoadFromRes Malloc2 failed\n")); // 100101
          WideCharToMultiByte(CP_ACP,                      // code page
                              0,                           // performance and mapping flags
                              (const WCHAR*)buf,           // wide-character string
                              l,                           // number of chars in string
                              b2,                          // buffer for new string
                              l+2,                         // size of buffer
                              NULL,                        // default for unmappable chars
                              NULL                         // set when default char used
                              );
          free(buf);
          buf=(char*)b2;
        }
#endif
#endif
      
      XMLNode x=XMLNode::parseString((LPTSTR)buf,tag,pResults);

      free(buf);
      return x;
    }