SEXP
R_connect_hWnd(SEXP className, SEXP excel_hWnd, SEXP raiseError)
{
  IUnknown *unknown = NULL;
  HRESULT hr;
  SEXP ans = R_NilValue;
  CLSID classId;
  LONG_PTR l_hwnd;
  HWND temp_hwdn;
  if(R_getCLSIDFromString(className, &classId) == S_OK) {
	l_hwnd = (LONG_PTR)INTEGER(excel_hWnd)[0];
	temp_hwdn = (HWND)l_hwnd;
    hr = AccessibleObjectFromWindow(temp_hwdn, OBJID_NATIVEOM, classId, (void**)&unknown);
    if(hr == S_OK) {
      void *ptr;
      hr = unknown->QueryInterface(IID_IDispatch, &ptr);
      ans = R_createRCOMUnknownObject((void *) ptr, "COMIDispatch");
    } else {
      if(LOGICAL(raiseError)[0]) {
	/* From COMError.cpp  - COMError */
	TCHAR buf[512];
	GetScodeString(hr, buf, sizeof(buf)/sizeof(buf[0]));
	PROTECT(ans = mkString(buf));
	SET_CLASS(ans, mkString("COMErrorString"));
	UNPROTECT(1);
        return(ans);
      } else
	return(R_NilValue);
    }
  } else {
      PROBLEM "Couldn't get clsid from the string"
	WARN;
  }
  return(ans);
}