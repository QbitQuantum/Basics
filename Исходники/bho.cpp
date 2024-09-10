HRESULT STDMETHODCALLTYPE adpbho::QueryInterface(
      REFIID riid, //Identifier of the requested interface
      void ** ppvObject //Address of output variable that receives the 
                        //interface pointer requested in iid
      ) {
  MB1("adpbho: QueryInterface");
  
  /*
adpbho: neither IID_IUnknown nor clsid_extie, {34A715A0-6587-11D0-924A-0020AFC7AC4D}
DIID_DWebBrowserEvents2

adpbho: neither IID_IUnknown nor clsid_extie, {49C3DE7C-D329-11D0-AB73-00C04FC33E80}
*/

  if ( riid == IID_IUnknown ) {
    *ppvObject = static_cast<adpbho*> (this);
  } 
  else if (riid == IID_IObjectWithSite) {
    // ::MessageBox(0, "Querying for IID_IObjectWithSite", 0, 0);
    *ppvObject = static_cast<IObjectWithSite*>(this);
    //::MessageBox(0,"XXXXXXXXXXXXXXXXXXXX", 0, 0);
    //char buf[50];
    //sprintf(buf, "%x", ppvObject 
    //static_cast<IObjectWithSite*>(*ppvObject)->SetSite(0);
  }
  else if (riid == IID_IDispatch) {
    // ::MessageBox(0, "Querying for IID_IDispatch", 0, 0);
    *ppvObject = static_cast<IDispatch*>(this);
    
    //unsigned int* x=new unsigned(4);
    //static_cast<IDispatch*>(this)->GetTypeInfoCount(x);
    //::MessageBox(0,"its an GotType", 0, 0);
  }
  else {
    // Information on StringFromCLSID can be found here:
    // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/com/cmf_a2c_05r8.asp
    wchar_t* buf;
    StringFromCLSID(riid, &buf);
    wchar_t buf1[150];
    wsprintfW(buf1, L"adpbho: neither IID_IUnknown nor clsid_extie, %s", buf);
	  ::CoTaskMemFree(buf);
    // ::MessageBoxW(0, buf1, 0, 0);
    
    *ppvObject = 0;
    return E_NOINTERFACE;
  }

	AddRef();
  return S_OK;
}