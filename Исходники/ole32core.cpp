// AutoWrap() - Automation helper function...
HRESULT OCVariant::AutoWrap(int autoType, VARIANT *pvResult,
  LPOLESTR ptName, OCVariant *argchain)
{
  // bug ? comment (see old ole32core.cpp project)
  // execute at the first time to safety free argchain
  // Allocate memory for arguments...
  unsigned int size = argchain ? argchain->size() : 0;
  VARIANT *pArgs = new VARIANT[size];
  OCVariant *p = argchain;
  for(unsigned int i = 0; p; i++, p = p->next){
    // bug ? comment (see old ole32core.cpp project)
    // will be reallocated BSTR whein using VariantCopy() (see by debugger)
    VariantInit(&pArgs[i]); // It will be free before copy.
    VariantCopy(&pArgs[i], &p->v);
  }
  if(argchain) delete argchain;
  // bug ? comment (see old ole32core.cpp project)
  // unexpected free original BSTR
  HRESULT hr = NULL;
  if(!v.pdispVal){
    checkOLEresult("Called with NULL IDispatch. AutoWrap");
    return hr;
  }
  // Convert down to ANSI (for error message only)
  char szName[256];
  WideCharToMultiByte(CP_ACP, 0,
    ptName, -1, szName, sizeof(szName), NULL, NULL);
  // Get DISPID for name passed...
  DISPID dispID;
  hr = v.pdispVal->GetIDsOfNames(IID_NULL, &ptName, 1,
    LOCALE_USER_DEFAULT, &dispID); // or _SYSTEM_ ?
  if(FAILED(hr)){
    ostringstream oss;
    oss << hr << " [" << szName << "] ";
    oss << "IDispatch::GetIDsOfNames AutoWrap";
    checkOLEresult(oss.str());
    return hr;
  }
  // Build DISPPARAMS
  DISPPARAMS dp = { NULL, NULL, 0, 0 };
  dp.cArgs = size;
  dp.rgvarg = pArgs;
  // Handle special-case for property-puts!
  DISPID dispidNamed = DISPID_PROPERTYPUT;
  if(autoType & DISPATCH_PROPERTYPUT){
    dp.cNamedArgs = 1;
    dp.rgdispidNamedArgs = &dispidNamed;
  }
  EXCEPINFO exceptInfo;
  // Make the call!
  hr = v.pdispVal->Invoke(dispID, IID_NULL,
    LOCALE_USER_DEFAULT, autoType, &dp, pvResult, &exceptInfo, NULL); // or _SYSTEM_ ?
  delete [] pArgs;
  if(FAILED(hr)){

	// Convert down to ANSI (for error message only)
  char szErrSource[256];
	int sourceLen = WideCharToMultiByte(CP_ACP, 0, exceptInfo.bstrSource, -1, szErrSource, sizeof(szErrSource), NULL, NULL);
	char szErrDescription[256];
	int descLen = WideCharToMultiByte(CP_ACP, 0, exceptInfo.bstrDescription, -1, szErrDescription, sizeof(szErrDescription), NULL, NULL);
  szErrSource[sourceLen] = 0;
  szErrDescription[descLen] = 0;

	ostringstream oss;
    oss << hr << " [" << szName << "] = [" << dispID << "]\r\n";
	oss << szErrSource << ": ";
	oss << szErrDescription << "\r\n";
    oss << "(It always seems to be appeared at that time you mistake calling ";
    oss << "'obj.get { ocv->getProp() }' <-> 'obj.call { ocv->invoke() }'.) ";
    oss << "IDispatch::Invoke AutoWrap";
    checkOLEresult(oss.str());
    return hr;
  }
  return hr;
}