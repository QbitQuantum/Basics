static BOOL DigiCrypt_IsValidCert(PCCERT_CONTEXT  pCertContext, BOOL fTimeCheck)
{
BOOL  fIsValid = FALSE;
BOOL  fRes = FALSE;
BYTE  bKeyUsageBits = CERT_NON_REPUDIATION_KEY_USAGE;
DWORD dwKeyUsageBytes = 1;
//Old version
//FILETIME oCurrentTime;
if (pCertContext != NULL && pCertContext->pCertInfo != NULL)
  {
  //not needed (info from Tarmo Milva)
  //if (DigiCrypt_CertIsSig(pCertContext) == TRUE)
    fRes = CertGetIntendedKeyUsage(X509_ASN_ENCODING,pCertContext->pCertInfo,&bKeyUsageBits,dwKeyUsageBytes);
  //else
  //  fRes = FALSE;
  if (fRes == TRUE)
    {
    if (bKeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE)
      fIsValid = TRUE;
	}
  if (fIsValid == TRUE && fTimeCheck == TRUE)
    {
    //Old version
    //GetSystemTimeAsFileTime(&oCurrentTime);
	  //if (CompareFileTime(&oCurrentTime, &pCertContext->pCertInfo->NotBefore) < 0 ||
		//    CompareFileTime(&oCurrentTime, &pCertContext->pCertInfo->NotAfter) > 0 )
    //  fIsValid = FALSE;
    //New version
    //NULL, if current datetime
    if (CertVerifyTimeValidity(NULL,pCertContext->pCertInfo) != 0)
      fIsValid = FALSE;
    }
  }
return(fIsValid);
}