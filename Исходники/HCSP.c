static int HCSP_setContext(void)
{
   int result = TRUE;

   LPSTR a = NULL;
   LPSTR b = NULL;
   LPSTR c = "My";

#ifdef DEBUG
   BIO_printf(err, "Call HCSP_setContext()\n");
#endif

#ifdef FILE_CONFIG
   readFileConfig(); /* get specified context provider, etc...  */

   if (pCryptProvider[0]     && strcasecmp(pCryptProvider,     "default")) a = pCryptProvider;
   if (pCryptContainer[0]    && strcasecmp(pCryptContainer,    "default")) b = pCryptContainer;
   if (pSubsystemProtocol[0] && strcasecmp(pSubsystemProtocol, "default")) c = pSubsystemProtocol;
#endif

#ifdef DEBUG
   strcpy(pSubsystemProtocol, c);

   BIO_printf(err, "Call HCSP_setContext()\n");
   BIO_printf(err, "pCryptProvider: \"%s\"\n", a);
   BIO_printf(err, "dwProviderType: %d\n", dwProviderType);
   BIO_printf(err, "pCryptContainer: \"%s\"\n", b);
   BIO_printf(err, "pSubsystemProtocol: \"%s\"\n", c);
   BIO_printf(err, "pFindPara: \"%s\"\n", pFindPara);
#endif

   /*
    * Set hCryptProvider to NULL to use the default CSP. If hCryptProvider is not NULL,
    * it must be a CSP handle created by using the CryptAcquireContext function.
    */

   if (!(hCertStore = CertOpenSystemStore(hCryptProvider, c)))
      {
#  ifdef DEBUG
      routine = "CertOpenSystemStore";
#  endif

      goto error;
      }

#ifdef DEBUG
   enumCertificate();
#endif

   if (!(pCertContext = CertFindCertificateInStore(
        hCertStore,
        (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING),
        0,
        CERT_FIND_SUBJECT_STR_A,
        pFindPara,
        NULL)))
      {
#  ifdef DEBUG
      routine = "CertFindCertificateInStore";
#  endif

      goto error;
      }

   if (!CryptAcquireCertificatePrivateKey(
      pCertContext,
      0,
      NULL,
      &hCryptProvider,
      &dwKeySpec,
      NULL))
      {
#  ifdef DEBUG
      routine = "CryptAcquireCertificatePrivateKey";
#  endif

      goto error;
      }

#ifdef DEBUG
   printInfo();
   enumKeyContainers();
   enumAlgorithms();

   printCertificate(pCertContext);
#endif

   bInitialized = TRUE;    /* set initialization flag */

   goto end;

error:

   result = FALSE;

end:

#ifdef DEBUG
   BIO_printf(err, "Return HCSP_setContext(%d)\n", result);
#endif

   return result;
}