/** This function has been modeled after http://perfectxml.com/CPPSOAP.asp, Section 3
*/
unsigned char* vvClient::getRegionHighLevel(int lod, int x0, int y0, int x1, int y1, 
  int startSlice, int endSlice, int id, const char*, const char*)
{
  unsigned char* ptr = NULL;
#ifdef HAVE_SOAP
  const char* WSDL_URL = 
      "http://129.114.6.157/region?wsdl";
//      "Z:\\projects\\tacc\\domain-checker.wsdl";
//      "Z:\\projects\\tacc\\region-current.wsdl";
//      "http://services.xmethods.net/soap/urn:xmethods-DomainChecker.wsdl";
//    "D:\\brown\\tacc\\region.wsdl";
//    "D:\\brown\\tacc\\xmethods-DomainChecker.wsdl";

#ifdef WIN32
  HRESULT hr;
  hr = CoInitialize(NULL);
  if (FAILED(hr))
  {
    cerr << "Error: CoInitialize failed" << endl;
    return NULL;
  }

  USES_CONVERSION;

  CComPtr<ISoapClient> spSOAPClient;
  hr = spSOAPClient.CoCreateInstance(CLSID_SoapClient30);
  if (FAILED(hr))
  { 
    cerr << "Error: CoCreateInstance failed ";
    if (hr==REGDB_E_CLASSNOTREG) cerr << "(CLASSNOTREG): is MS SOAP Toolkit 3.0 installed?" << endl;
    else cerr << "hr=" << hr << endl;
    return NULL;
  }

  cerr << "Using WSDL file: " << WSDL_URL << endl;
  try
  {
//    spSOAPClient->PutConnectorProperty("AuthUser", "PRODUCTION\\webService");
    spSOAPClient->PutConnectorProperty("AuthUser", "PRODUCTION\\webservice");
    spSOAPClient->PutConnectorProperty("AuthPassword", "webservice");
    spSOAPClient->PutConnectorProperty("EndPointURL", "http://129.114.6.157/region/?wsdl");
//    hr = spSOAPClient->MSSoapInit(_bstr_t(WSDL_URL), L"", L"", L"");  // WSDL, service, port, WSML
    hr = spSOAPClient->MSSoapInit(_bstr_t(WSDL_URL), L"EP_SQLCT", L"EP_SQLCT", L"");
  }
  catch(_com_error &e)
  {
    cerr << "Exception: spSOAPClient->MSSoapInit failed. ";
    hr = e.Error();
    if (FAILED(hr))
    {
      if (hr==E_INVALIDARG) cerr << "E_INVALIDARG" << endl;
      else if (hr==OLE_E_BLANK) cerr << "OLE_E_BLANK" << endl;
      else cerr << "hr=" << hr << endl;
    }
    return NULL;
  }
  if (FAILED(hr))
  {
    cerr << "Error: spSOAPClient->MSSoapInit failed" << endl;
    return NULL;
  }

  // Set login information
  // (find more information and parameters at
  // http://www.c-sharpcorner.com/Code/2004/May/SOAPClient.asp):
//  spSOAPClient->PutConnectorProperty("AuthUser", "PRODUCTION\\webservice");
  spSOAPClient->PutConnectorProperty("AuthUser", "PRODUCTION\\webService");
  spSOAPClient->PutConnectorProperty("AuthPassword", "webservice");
//  spSOAPClient->PutConnectorProperty("WinHTTPAuthScheme", "24"); // or 1?

  // Call the Web Service method:
  WCHAR* pwcMethodName = L"GetRegion";
  DISPID dispidFn = 0;
  hr = spSOAPClient->GetIDsOfNames(IID_NULL, &pwcMethodName, 1, 
    LOCALE_SYSTEM_DEFAULT, &dispidFn);
  if (FAILED(hr))
  {
    cerr << "Error: GetIDsOfNames failed" << endl;
    return NULL;
  }

  // Set parameter set for call to 
  // GetRegion(lod, x0, y0, x1, y1, startSlice, endSlice, id):
  unsigned int uArgErr;
  VARIANT varg[8];
  varg[0].vt = VT_INT;
  varg[0].intVal = lod;
  varg[1].vt = VT_INT;
  varg[1].intVal = x0;
  varg[2].vt = VT_INT;
  varg[2].intVal = y0;
  varg[3].vt = VT_INT;
  varg[3].intVal = x1;
  varg[4].vt = VT_INT;
  varg[4].intVal = y1;
  varg[5].vt = VT_INT;
  varg[5].intVal = startSlice;
  varg[6].vt = VT_INT;
  varg[6].intVal = endSlice;
  varg[7].vt = VT_INT;
  varg[7].intVal = id;

  DISPPARAMS params;
  params.cArgs = 8;
  params.rgvarg = varg;
  params.cNamedArgs = 0;
  params.rgdispidNamedArgs = NULL;

  _variant_t result;

  uArgErr = (unsigned int)-1;

  cerr << "spSOAPClient->Invoke" << endl;
  EXCEPINFO excepInfo;
  memset(&excepInfo, 0, sizeof(excepInfo));
  hr  = spSOAPClient->Invoke(dispidFn, IID_NULL, LOCALE_SYSTEM_DEFAULT, 
    DISPATCH_METHOD, &params, &result, &excepInfo, &uArgErr);
  if (FAILED(hr))
  {
    cerr << "Error: Invoke failed" << endl;
    return NULL;
  }

  if(result.vt != VT_PTR)
  {
    cerr << "Error: Invalid return type" << endl;
    return NULL;
  }
  ptr = (unsigned char*)result.pcVal;

  CoUninitialize();
#endif
#else
  (void)lod;
  (void)x0;
  (void)y0;
  (void)x1;
  (void)y1;
  (void)startSlice;
  (void)endSlice;
  (void)id;
#endif
  
  return ptr;
}