SEXP R_proxy_info(){
  WINHTTP_CURRENT_USER_IE_PROXY_CONFIG MyProxyConfig;
  if(!WinHttpGetIEProxyConfigForCurrentUser(&MyProxyConfig)){
    return R_NilValue;
  }
  char buffer[500];
  SEXP vec = PROTECT(allocVector(VECSXP, 4));
  SET_VECTOR_ELT(vec, 0, ScalarLogical(MyProxyConfig.fAutoDetect));

  if(MyProxyConfig.lpszAutoConfigUrl != NULL) {
    wcstombs(buffer, MyProxyConfig.lpszAutoConfigUrl, 500);
    SET_VECTOR_ELT(vec, 1, mkString(buffer));
  }

  if(MyProxyConfig.lpszProxy != NULL) {
    wcstombs(buffer, MyProxyConfig.lpszProxy, 500);
    SET_VECTOR_ELT(vec, 2, mkString(buffer));
  }

  if(MyProxyConfig.lpszProxyBypass != NULL) {
    wcstombs(buffer, MyProxyConfig.lpszProxyBypass, 500);
    SET_VECTOR_ELT(vec, 3, mkString(buffer));
  }
  setAttrib(vec, R_NamesSymbol, proxy_namesvec());
  UNPROTECT(1);
  return vec;
}