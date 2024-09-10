BOOL AcquireAndGetRSAKey(PCCERT_CONTEXT pCertContext,
                         HCRYPTPROV *phProv,
                         HCRYPTKEY *phRSAKey,
                         BOOL fEncrypt,
                         BOOL *pfCallerFreeProv)
{
    BOOL fSuccess = FALSE;
    DWORD dwKeySpec = 0;

    __try
    {
        *phProv = NULL;
        *phRSAKey = NULL;
        *pfCallerFreeProv = FALSE;

        if (fEncrypt)
        {
            // Acquire context for RSA key
            fSuccess = CryptAcquireContext(phProv,
                                           NULL,
                                           MS_DEF_PROV,
                                           PROV_RSA_FULL,
                                           CRYPT_VERIFYCONTEXT);
            if (!fSuccess)
            {
                MyPrintf(_T("CryptAcquireContext failed with %X\n"), GetLastError());
                __leave;
            }

            // Import the RSA public key from the certificate context
            fSuccess = CryptImportPublicKeyInfo(*phProv,
                                                MY_ENCODING,
                                                &(pCertContext->pCertInfo->SubjectPublicKeyInfo),
                                                phRSAKey);
            if (!fSuccess)
            {
                MyPrintf(_T("CryptImportPublicKeyInfo failed with %X\n"), GetLastError());
                __leave;
            }

            *pfCallerFreeProv = TRUE;
        }
        else
        {
            // Acquire the RSA private key
            fSuccess = CryptAcquireCertificatePrivateKey(pCertContext,
                       CRYPT_ACQUIRE_USE_PROV_INFO_FLAG|CRYPT_ACQUIRE_COMPARE_KEY_FLAG,
                       NULL, phProv, &dwKeySpec, pfCallerFreeProv);
            if (!fSuccess)
            {
                MyPrintf(_T("CryptAcquireCertificatePrivateKey failed with %X\n"), GetLastError());
                __leave;
            }

            // Get the RSA key handle
            fSuccess = CryptGetUserKey(*phProv, dwKeySpec, phRSAKey);
            if (!fSuccess)
            {
                MyPrintf(_T("CryptGetUserKey failed with %X\n"), GetLastError());
                __leave;
            }
        }
    }
    __finally
    {
        if (fSuccess == FALSE)
        {
            if (phProv && *phProv != NULL)
            {
                CryptReleaseContext(*phProv, 0);
                *phProv = NULL;
            }
            if (phRSAKey && *phRSAKey != NULL)
            {
                CryptDestroyKey(*phRSAKey);
                *phRSAKey = NULL;
            }
        }
    }

    return fSuccess;
}