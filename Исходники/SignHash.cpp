BOOL GetRSAKeyFromCert(PCCERT_CONTEXT pCertContext,
                       BOOL fSign,
                       HCRYPTPROV *hProv,
                       HCRYPTKEY *hPubKey,
                       DWORD *dwKeySpec,
                       BOOL *fFreeProv)
{   
   BOOL fResult;
   BOOL fReturn = FALSE;
   
   __try
   {  
      if (hProv == NULL || hPubKey == NULL || 
          dwKeySpec == NULL || fFreeProv == NULL)
      {
         __leave;
      }

      *hProv = 0;
      *hPubKey = 0;
      *fFreeProv = FALSE;
    
      if (fSign)
      {
         // Acquire the certificate's private key
         fResult = CryptAcquireCertificatePrivateKey(pCertContext,
                                                     CRYPT_ACQUIRE_USE_PROV_INFO_FLAG|
                                                     CRYPT_ACQUIRE_COMPARE_KEY_FLAG,
                                                     NULL,
                                                     hProv,
                                                     dwKeySpec,
                                                     fFreeProv);
         if (!fResult)
         {
            MyPrintf(_T("CryptAcquireCertificatePrivateKey failed with %x\n"), GetLastError());
            __leave;
         }
      }
      else
      {
         fResult = CryptAcquireContext(hProv, 
                                       NULL, 
                                       MS_DEF_PROV,
                                       PROV_RSA_FULL, 
                                       CRYPT_VERIFYCONTEXT);
         if (!fResult)
         {
            MyPrintf(_T("CryptAcquireContext failed with %x\n"), GetLastError());
            __leave;
         }

         *fFreeProv = TRUE;

         // Import the public key from the certificate so we can verify
         fResult = CryptImportPublicKeyInfo(*hProv,
                                            ENCODING,
                                            &(pCertContext->pCertInfo->SubjectPublicKeyInfo),
                                            hPubKey);
         if (!fResult)
         {
            MyPrintf(_T("CryptImportPublicKeyInfo failed with %x\n"), GetLastError());
            __leave;
         }         
      }

      fReturn = TRUE;
   }
   __finally
   {
      if (!fReturn)
      {
         if (*hPubKey != NULL) 
         {
            CryptDestroyKey(*hPubKey);
            *hPubKey = NULL;
         }

         if ((*fFreeProv == TRUE) && (*hProv != NULL)) 
         {
            CryptReleaseContext(*hProv, 0);
            *hProv = NULL;
            *fFreeProv = FALSE;
         }
      }
   }

   return fReturn;
}