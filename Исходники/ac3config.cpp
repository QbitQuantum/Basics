LONG CALLBACK CPlApplet(HWND hwndCPL, UINT uMsg, LPARAM lParam1, LPARAM lParam2) 
{ 
  ISpecifyPropertyPages *spp;
  CAUUID cauuid;
  HRESULT hr;
  LPCPLINFO lpCPlInfo; 
  
  switch (uMsg) 
  { 
  case CPL_INIT:      // first message, sent once 
    hinst = GetModuleHandle("ac3filter.ax");
    return TRUE; 
    
  case CPL_GETCOUNT:  // second message, sent once 
    return 1;
    break; 
    
  case CPL_INQUIRE:   // third message, sent once per application 
    lpCPlInfo = (LPCPLINFO) lParam2; 
    lpCPlInfo->lData = 0; 
    lpCPlInfo->idIcon = IDI_AC3FILTER;
    lpCPlInfo->idName = IDS_AC3FILTER;
    lpCPlInfo->idInfo = IDS_DESC;
    break; 
    
  case CPL_DBLCLK:    // application icon double-clicked 
    CoInitialize(0);
    warning();
    hr = CoCreateInstance(CLSID_AC3Filter, NULL, CLSCTX_INPROC_SERVER, IID_ISpecifyPropertyPages, (LPVOID *)&spp);
    hr = spp->GetPages(&cauuid);
    hr = OleCreatePropertyFrame(0, 30, 30, NULL, 1, (IUnknown **)&spp, cauuid.cElems, (GUID *)cauuid.pElems, 0, 0, NULL);
    CoTaskMemFree(cauuid.pElems);
    spp->Release();
    CoUninitialize();
    break; 
    
  case CPL_STOP:      // sent once per application before CPL_EXIT 
    break; 
    
  case CPL_EXIT:      // sent once before FreeLibrary is called 
    break; 
    
  default: 
    break; 
  } 
  return 0; 
} 