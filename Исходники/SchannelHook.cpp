/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
SECURITY_STATUS SchannelHook::InitializeSecurityContextW(
    PCredHandle phCredential,
    PCtxtHandle phContext, SEC_WCHAR * pszTargetName, 
    unsigned long fContextReq, unsigned long Reserved1,
    unsigned long TargetDataRep, PSecBufferDesc pInput,
    unsigned long Reserved2, PCtxtHandle phNewContext,
    PSecBufferDesc pOutput, unsigned long * pfContextAttr,
    PTimeStamp ptsExpiry) {
  SECURITY_STATUS ret = SEC_E_INTERNAL_ERROR;
  fContextReq |= ISC_REQ_MANUAL_CRED_VALIDATION;
  if (_InitializeSecurityContextW) {
    ret = _InitializeSecurityContextW(phCredential, phContext,
            pszTargetName, fContextReq, Reserved1, TargetDataRep, pInput,
            Reserved2, phNewContext, pOutput, pfContextAttr, ptsExpiry);
    if (!phContext && phNewContext) {
    }
  }

  if (tlsIndex != TLS_OUT_OF_INDEXES)
    TlsSetValue(tlsIndex, phContext ? phContext : phNewContext);
  return ret;
}