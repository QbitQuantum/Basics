static void test_getObjectUrl(void)
{
    BOOL ret;
    DWORD urlArraySize = 0, infoSize = 0;
    PCCERT_CONTEXT cert;

    SetLastError(0xdeadbeef);
    ret = CryptGetObjectUrl(NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());
    /* Crash
    ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, NULL, 0, NULL, NULL,
     NULL, NULL, NULL);
    ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, NULL, 0, NULL, NULL,
     NULL, &infoSize, NULL);
    ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, NULL, 0, NULL,
     &urlArraySize, NULL, &infoSize, NULL);
     */
    /* A cert with no CRL dist point extension fails.. */
    cert = CertCreateCertificateContext(X509_ASN_ENCODING, bigCert,
     sizeof(bigCert));
    SetLastError(0xdeadbeef);
    ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert, 0, NULL,
     NULL, NULL, NULL, NULL);
    ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
     "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
    CertFreeCertificateContext(cert);

    cert = CertCreateCertificateContext(X509_ASN_ENCODING,
     certWithIssuingDistPoint, sizeof(certWithIssuingDistPoint));
    if (cert)
    {
        /* This cert has no AIA extension, so expect this to fail */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert, 0,
         NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert,
         CRYPT_GET_URL_FROM_PROPERTY, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert,
         CRYPT_GET_URL_FROM_EXTENSION, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        /* It does have an issuing dist point extension, but that's not what
         * this is looking for (it wants a CRL dist points extension)
         */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, 0, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, CRYPT_GET_URL_FROM_PROPERTY, NULL, NULL, NULL, NULL,
         NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, CRYPT_GET_URL_FROM_EXTENSION, NULL, NULL, NULL, NULL,
         NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        CertFreeCertificateContext(cert);
    }
    cert = CertCreateCertificateContext(X509_ASN_ENCODING,
     certWithCRLDistPoint, sizeof(certWithCRLDistPoint));
    if (cert)
    {
        PCRYPT_URL_ARRAY urlArray;

        /* This cert has no AIA extension, so expect this to fail */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert, 0,
         NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert,
         CRYPT_GET_URL_FROM_PROPERTY, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void *)cert,
         CRYPT_GET_URL_FROM_EXTENSION, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        /* It does have a CRL dist points extension */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, 0, NULL, NULL, NULL, NULL, NULL);
        ok(!ret && GetLastError() == E_INVALIDARG,
         "Expected E_INVALIDARG, got %08x\n", GetLastError());
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, 0, NULL, NULL, NULL, &infoSize, NULL);
        ok(!ret && GetLastError() == E_INVALIDARG,
         "Expected E_INVALIDARG, got %08x\n", GetLastError());
        /* Can get it without specifying the location: */
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, 0, NULL, &urlArraySize, NULL, NULL, NULL);
        ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
        urlArray = HeapAlloc(GetProcessHeap(), 0, urlArraySize);
        if (urlArray)
        {
            ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
             (void *)cert, 0, urlArray, &urlArraySize, NULL, NULL, NULL);
            ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
            if (ret)
            {
                LPWSTR pUrl = url;
                CRYPT_URL_ARRAY expectedUrl = { 1, &pUrl };

                compareUrlArray(&expectedUrl, urlArray);
            }
            HeapFree(GetProcessHeap(), 0, urlArray);
        }
        /* or by specifying it's an extension: */
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, CRYPT_GET_URL_FROM_EXTENSION, NULL, &urlArraySize, NULL,
         NULL, NULL);
        ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
        urlArray = HeapAlloc(GetProcessHeap(), 0, urlArraySize);
        if (urlArray)
        {
            ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
             (void *)cert, CRYPT_GET_URL_FROM_EXTENSION, urlArray,
             &urlArraySize, NULL, NULL, NULL);
            ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
            if (ret)
            {
                LPWSTR pUrl = url;
                CRYPT_URL_ARRAY expectedUrl = { 1, &pUrl };

                compareUrlArray(&expectedUrl, urlArray);
            }
            HeapFree(GetProcessHeap(), 0, urlArray);
        }
        /* but it isn't contained in a property: */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, CRYPT_GET_URL_FROM_PROPERTY, NULL, &urlArraySize, NULL,
         NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "Expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        CertFreeCertificateContext(cert);
    }
    cert = CertCreateCertificateContext(X509_ASN_ENCODING,
     certWithAIAWithCAIssuers, sizeof(certWithAIAWithCAIssuers));
    if (cert)
    {
        PCRYPT_URL_ARRAY urlArray;

        /* This has an AIA extension with the CA Issuers set, so expect it
         * to succeed:
         */
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER,
         (void *)cert, 0, NULL, &urlArraySize, NULL, NULL, NULL);
        ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
        if (ret)
        {
            urlArray = HeapAlloc(GetProcessHeap(), 0, urlArraySize);
            if (urlArray)
            {
                ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER,
                 (void *)cert, CRYPT_GET_URL_FROM_EXTENSION, urlArray,
                 &urlArraySize, NULL, NULL, NULL);
                ok(ret, "CryptGetObjectUrl failed: %08x\n", GetLastError());
                if (ret)
                {
                    LPWSTR pUrl = url;
                    CRYPT_URL_ARRAY expectedUrl = { 1, &pUrl };

                    compareUrlArray(&expectedUrl, urlArray);
                }
                HeapFree(GetProcessHeap(), 0, urlArray);
            }
        }
        /* It doesn't have a CRL dist points extension, so this should fail */
        SetLastError(0xdeadbeef);
        ret = CryptGetObjectUrl(URL_OID_CERTIFICATE_CRL_DIST_POINT,
         (void *)cert, 0, NULL, &urlArraySize, NULL, NULL, NULL);
        ok(!ret && GetLastError() == CRYPT_E_NOT_FOUND,
         "expected CRYPT_E_NOT_FOUND, got %08x\n", GetLastError());
        CertFreeCertificateContext(cert);
    }
}