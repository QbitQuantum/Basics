LRESULT nsf_window::onCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  RECT rcClient;
  GetClientRect(&rcClient);
  
  // get nsd/nsf
  unsigned long params[2];
  params[0] = (unsigned long)&nsf;
  params[1] = (unsigned long)&nsd;
  SendMessageRoot(MSG_GET_NSD, (WPARAM)0, (LPARAM)params);
  
  mainList   = new entryList(IDC_MAINTREE,       ENTRYLIST_NSF, nsf, nsd,   0, 0, 200, rcClient.bottom, hSelf);
  globalList = new entryList(IDC_GLOBALTREE, ENTRYLIST_DEFAULT, nsf, nsd, 484, 0, 118, rcClient.bottom, hSelf);
  lookupList = new entryList(IDC_LOOKUPTREE,     ENTRYLIST_NSD, nsf, nsd, 602, 0, 236, rcClient.bottom, hSelf);	  

  //484, 354
  hCodeMenu = CreatePopupMenu();
  AppendMenu(hCodeMenu, MF_STRING, ID_GOOL_VIEW, "Open in Code View");
   
  hModelMenuA = CreatePopupMenu();
  AppendMenu(hModelMenuA, MF_STRING, ID_MODEL_VIEW, "Open in Model/Zone View"); 
  AppendMenu(hModelMenuA, MF_SEPARATOR, ID_SEPARATOR, "");
  AppendMenu(hModelMenuA, MF_STRING, ID_MODEL_EXPORT_AS_COLLADA, "Export as COLLADA");    
      
  hModelMenuB = CreatePopupMenu();
  AppendMenu(hModelMenuB, MF_STRING, ID_MODEL_EXPORT_AS_MD3, "Export as .MD3");
  
  CreateWindowEx(0, WC_STATIC, "",
    WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME,
    210, 10, 250, 110,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "Type: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 25, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "Entry Count: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 55, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "Checksum: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 85, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 25, 100, 22, 
    hSelf, (HMENU)IDC_CHUNKTYPEEDIT, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 55, 100, 22, 
    hSelf, (HMENU)IDC_CHUNKENTRYCOUNTEDIT, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 85, 100, 22, 
    hSelf, (HMENU)IDC_CHUNKCHECKSUMEDIT, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "",
    WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME,
    210, 130, 250, 110,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "Type: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 145, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "Item Count: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 175, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(0, WC_STATIC, "n/a: ",
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    220, 205, 110, 22,
    hSelf, NULL, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 145, 100, 22, 
    hSelf, (HMENU)IDC_ENTRYTYPEEDIT, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 175, 100, 22, 
    hSelf, (HMENU)IDC_ENTRYITEMCOUNTEDIT, hInstance, NULL);

  CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
    WS_CHILD | WS_VISIBLE, 
    320, 205, 100, 22, 
    hSelf, (HMENU)IDC_UNUSEDEDIT, hInstance, NULL);
    
  mainList->occupy();
  lookupList->occupy();
		  
  for (int lp=0; lp<MAX_LEVELEIDS; lp++)
    globalList->lookupAddEntry(nsd->levelEIDs[lp]);


  return NULL; }