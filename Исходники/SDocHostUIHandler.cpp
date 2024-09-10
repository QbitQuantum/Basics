 //////////////////////////////////////////////////////////////////////////
 // CImpIDispatch
 bool CallCpp(LPCWSTR pszParam)
 {
     return MessageBoxW(GetActiveWindow(),pszParam,L"jscall",MB_OKCANCEL)==IDOK?true:false;
 }