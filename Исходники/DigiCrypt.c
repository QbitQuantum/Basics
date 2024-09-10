static BOOL DigiCrypt_IsValidCert(PCCERT_CONTEXT  pCertContext, BOOL fTimeCheck)
{
BOOL  fIsValid = FALSE;
BOOL  fRes = FALSE;
BOOL  fKuCheck = TRUE;
BYTE  bKeyUsageBits = CERT_NON_REPUDIATION_KEY_USAGE;
DWORD dwKeyUsageBytes = 1;
// VS use auth certs if key_usage_check = 0
fKuCheck = (BOOL)ConfigItem_lookup_int("KEY_USAGE_CHECK", 1);
bKeyUsageBits = fKuCheck ? CERT_NON_REPUDIATION_KEY_USAGE : 0;
//LOG("KEY_USAGE_CHECK: %d ku: %d", fKuCheck, bKeyUsageBits); 
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
    //LOG("KU non-repu: %d", (bKeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE));
    if(!fKuCheck || (bKeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE))
	  fIsValid = TRUE;
    if(bKeyUsageBits & CERT_KEY_CERT_SIGN_KEY_USAGE) // don't display CA certs
	  fIsValid = FALSE;
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